//coding:utf-8
/**********************************************
Program: Normalization class cpp file
Description: 
Author: cshanbo@gmail.com
Date: 2016-09-08 09:42:43
Last modified: 2016-09-08 10:33:10
**********************************************/

#include <string>
#include "../include/normalization.h"

Normalization::Normalization() {}

Normalization::Normalization(std::string DICT_PATH, std::string HMM_PATH, std::string USER_DICT_PATH) {
    segmenter = new cppjieba::Jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH);
}

Normalization::~Normalization() {
    delete segmenter;
}
