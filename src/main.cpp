//coding:utf-8
/*
Program: test
Description: 
Date: 2016-07-05 21:07:39
Last modified: 2016-09-08 10:38:09
GCC version: 4.7.3
*/

#include <iostream>
#include <fstream>
#include <string>
#include <pcrecpp.h>

#include "../include/util.h"
#include "../include/normalization.h"
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


    const string DICT_PATH = "./3rd/dict/jieba.dict.utf8";
    const string HMM_PATH = "./3rd/dict/hmm_model.utf8";
    const string USER_DICT_PATH = "./3rd/dict/user.dict.utf8";

    cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH);
    Normalization* norm = new Normalization(DICT_PATH, HMM_PATH, USER_DICT_PATH);
    s = "小明硕士毕业于中国科学院计算所后在日本京都大学深造";
    std::vector<cppjieba::Word> jiebawords;
    norm->segmenter->CutForSearch(s, jiebawords, true);
    // jieba.CutForSearch(s, jiebawords, true);
    cout << s << endl;
    for(auto jbwd: jiebawords) {
        cout << jbwd.word << '\t' << jbwd.offset << "-" << jbwd.offset + jbwd.word.length() << endl;
    }
}
