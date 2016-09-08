//coding:utf-8
/**********************************************
Program: Normalization interface
Description: 
Author: cshanbo@gmail.com
Date: 2016-09-08 09:25:22
Last modified: 2016-09-08 09:25:22
**********************************************/


#ifndef _NORMALIZATION_H_
#define _NORMALIZATION_H_


#include <string>
#include "../3rd/include/Jieba.hpp"

class Normalization {
public:
    Normalization();
    ~Normalization();

    Normalization(std::string, std::string, std::string);

    cppjieba::Jieba* segmenter = NULL;
};

#endif
