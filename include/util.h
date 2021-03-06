//coding:utf-8
/*
Program: string process util
Description: 
Shanbo Cheng: scheng@ancestry.com
Date: 2016-07-05 20:38:33
Last modified: 2016-07-05 20:45:35
GCC version: 4.9.3
*/

#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <string>
#include <vector>

#include "parameters.h"

using namespace std;

void split(const string &src, const string &separator, vector<string> &dest_list);

string &trim(string &line);

void stringReplace(string &origin, const string &src, const string &tgt);

int segWords(SingleLineResult&, cppjieba::Jieba&);

int getContext(RecogObj&, SingleLineResult&);

bool splitterJudge(std::string str);

#endif
