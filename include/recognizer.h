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

#include "util.h"
#include "regularRule.h"
#include "parameters.h"
#include "../3rd/include/Jieba.hpp"


class Recognizer {
public:
    Recognizer();
    ~Recognizer();

    cppjieba::Jieba* segmenter = NULL;

    Recognizer(std::string, std::string, std::string, std::string, bool, bool); // first 3 parameters are to initialize the word segmenter. Could be written in hard codes

    RegularRule* _rule_list;

    int readRegexRules(std::string conf_file);

    void initRegexSet(std::string);

};

#endif
