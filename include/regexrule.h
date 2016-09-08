//coding:utf-8
/***********************************************************
Program: Regular expression rules
Description: 
Shanbo Cheng: cshanbo@gmail.com
Date: 2016-09-08 16:10:57
Last modified: 2016-09-08 16:10:57
GCC version: 4.9.3
***********************************************************/


#ifndef _REGEX_RULE_H
#define _REGEX_RULE_H

#include <string>
#include <vector>
#include <pcrecpp.h>

#include "parameters.h"

class RegularRule {
    pcrecpp::RE* _re;
public:
    RegularRule();
    ~RegularRule();

    std::string _name;
    std::string _tag;
    std::string _re_str;

    int _priority;
    int _confidence;
    int analysis(const string&);
    int analysisPattern(const string);
    int recog(SingleLineResult&, std::vector<RecogObj>&);
    int recogOnce(SingleLineResult&, int);  //int is used as offset
    int setIndex(int);
};

#endif
