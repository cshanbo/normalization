//coding:utf-8
/*
Program: test
Description: 
Date: 2016-07-05 21:07:39
Last modified: 2016-09-07 15:09:01
GCC version: 4.7.3
*/

#include <iostream>
#include <fstream>
#include <string>
#include <pcrecpp.h>

#include "../include/util.h"
#include "./3rd/include/Jieba.hpp"

using namespace std;

int show_usage() {
    std::cout << "usage: cmd + input_file + result_file" << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        show_usage();
        exit(0);
    }

    string root_dir = "../conf";
    std::ifstream ifs(argv[1], std::ios::in);

    string line = "";
    while(ifs) {
        if(getline(ifs, line)) {
            trim(line);
            cout << line << endl;
        }
    }
    int i;
    string s;
    pcrecpp::RE re("(\\w+):(\\d+)");
    if (re.error().length() > 0) {
        std::cout << "PCRE compilation failed with error: " << re.error() << "\n";
    }
    if (re.PartialMatch("root:1234", &s, &i))
    std::cout << s << " : " << i << std::endl;


    const char* const DICT_PATH = "./3rd/dict/jieba.dict.utf8";
    const char* const HMM_PATH = "./3rd/dict/hmm_model.utf8";
    const char* const USER_DICT_PATH = "./3rd/dict/user.dict.utf8";
    const char* const IDF_PATH = "./3rd/dict/idf.utf8";
    const char* const STOP_WORD_PATH = "./3rd/dict/stop_words.utf8";
    cppjieba::Jieba jieba(DICT_PATH, 
            HMM_PATH, 
            USER_DICT_PATH);
    vector<string> words;
    vector<cppjieba::Word> jiebawords;
    string result;

    s = "小明硕士毕业于中国科学院计算所后在日本京都大学深造";
    cout << "[demo] CutForSearch Word With Offset" << endl;
    jieba.CutForSearch(s, jiebawords, true);
    cout << jiebawords << endl;
}
