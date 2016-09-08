//coding:utf-8
/**********************************************
Program: Normalization class cpp file
Description: 
Author: cshanbo@gmail.com
Date: 2016-09-08 09:42:43
Last modified: 2016-09-08 15:54:44
**********************************************/

#include <string>
#include "../include/Recognizer.h"

Recognizer::Recognizer() {
    segmenter = NULL;
}

Recognizer::Recognizer(std::string DICT_PATH, std::string HMM_PATH, std::string USER_DICT_PATH, std::string conf_dir, bool use_segment, bool use_classifier) {
    segmenter = new cppjieba::Jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH);
}

Recognizer::~Recognizer() {
    delete segmenter;
}

