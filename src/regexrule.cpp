//coding:utf-8
/***********************************************************
Program: Regular expression rules cpp
Description: 
Shanbo Cheng: cshanbo@gmail.com
Date: 2016-09-08 16:20:03
Last modified: 2016-09-08 16:37:23
GCC version: 4.9.3
***********************************************************/

#include <iostream>

#include "../include/regexrule.h"
#include "../include/util.h"

int RegularRule::analysis(const string& input) {
    std::vector<string> regular_conf_list;
    split(input, "\t", regular_conf_list);
    if(regular_conf_list.size() != 4) {
        std::cerr << "regex pattern error: " << input << std::endl;
        return -1;
    }
    this->_name = regular_conf_list[0];
    this->_tag = regular_conf_list[1];
    this->_priority = atoi(regular_conf_list[2].c_str());
    this->_re_str = regular_conf_list[3];

    return 0;
}
