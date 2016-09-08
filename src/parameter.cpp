//coding:utf-8
/**********************************************
Program: Implementation of parameter
Description: 
Author: cshanbo@gmail.com
Date: 2016-09-07 15:43:39
Last modified: 2016-09-08 10:49:24
**********************************************/


#include "../include/parameters.h"

SingleLineResult::SingleLineResult() {
    for (int i = 0; i < REGEX_RULE_COUNT; ++i)
        end_index[i] = -1;
    // pout = NULL;
    // if((pout = scw_create_out(MAX_TERM_COUNT * 2, SCW_OUT_FLAG)) == NULL) {
    //     std::cerr << "error: initializing the output buffer error." << std::endl;
    //     return;
    // }
}

int SingleLineResult::clear() {
    current_line = "";
    unicode_string_list.clear();
    index_map.clear();
    reversed_index_map.clear();
    word_list.clear();
    result_list.clear();
    feature_map.clear();
    for (int i = 0; i < REGEX_RULE_COUNT; ++i)
        end_index[i] = -1;
    return 0;
}

SingleLineResult::~SingleLineResult() {
    clear();
}
