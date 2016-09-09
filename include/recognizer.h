//coding:utf-8
/**********************************************
Program: Normalization interface
Description: 
Author: cshanbo@gmail.com
Date: 2016-09-08 09:25:22
Last modified: 2016-09-08 09:25:22
**********************************************/


#ifndef _RECOGNIZER_H_
#define _RECOGNIZER_H_


#include <string>
#include <iostream>

#include "parameters.h"

#include "util.h"
#include "../3rd/include/Jieba.hpp"
#include "regularRule.h"

class Recognizer {
public:
    Recognizer();
    ~Recognizer();

    Recognizer(std::string, std::string, std::string, std::string, bool, bool); // first 3 parameters are to initialize the word segmenter. Could be written in hard codes

    RegularRule* _rule_list;
    int readRegexRules(std::string conf_file) {
        std::ifstream ifs(conf_file.c_str(), std::ios::in); 
        if (!ifs) {
            std::cerr << "Regex configuration file doesn't exist: "<< conf_file << std::endl;
            return -1;
        }
        int i = 0;
        std::string input_line = "";

        while(ifs && i < REGEX_RULE_COUNT) {
            if(getline(ifs, input_line)) {
                if(input_line.empty())
                    continue;
                if(input_line[0] == '#')
                    continue;
                trim(input_line);
                this->_rule_list[i].analysis(input_line);
                this->_rule_list[i].setIndex(i);
                ++i;
            }
        }
        if (i != REGEX_RULE_COUNT) {
            cerr << "Rules number is less than REGEX_RULE_COUNT: " << conf_file << endl;
            exit(-1);
        }
        ifs.close();
        return 0;
    }

    cppjieba::Jieba* segmenter;
};

#endif
