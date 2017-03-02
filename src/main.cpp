//coding:utf-8
/*
Program: test
Description: 
Date: 2016-07-05 21:07:39
Last modified: 2017-03-02 20:49:07
GCC version: 4.7.3
*/

#include <iostream>
#include <fstream>
#include <string>
#include <pcrecpp.h>

#include "../include/util.h"
#include "../include/recognizer.h"
#include "../3rd/include/Jieba.hpp"

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

    int i;
    string s;
    pcrecpp::RE re("(\\w+):(\\d+)");
    if (re.error().length() > 0) {
        std::cout << "PCRE compilation failed with error: " << re.error() << "\n";
    }


    const string DICT_PATH = "../3rd/dict/jieba.dict.utf8";
    const string HMM_PATH = "../3rd/dict/hmm_model.utf8";
    const string USER_DICT_PATH = "../3rd/dict/user.dict.utf8";

    cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH);
    Recognizer* norm = new Recognizer(DICT_PATH, HMM_PATH, USER_DICT_PATH, root_dir, 1, 1);
    // string line = "";
    // std::ifstream ifs(argv[1], std::ios::in);
    // while(ifs) {
    //     if(getline(ifs, line)) {
    //         trim(line);
    //         std::vector<cppjieba::Word> jiebawords;
    //         norm->segmenter->Cut(line, jiebawords, true);
    //         for(auto jbwd: jiebawords) {
    //             cout << jbwd.word << " ";
    //             // cout << jbwd.word << '\t' << jbwd.offset << "-" << jbwd.offset + jbwd.word.length() << endl;
    //         }
    //     }
    // }
    return 0;
}
