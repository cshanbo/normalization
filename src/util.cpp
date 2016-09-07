//coding:utf-8
/*
Program: util.cpp basic functions
Description: 
Shanbo Cheng: cshanbo@gmail.com
Date: 2016-07-05 20:46:23
Last modified: 2016-09-07 14:28:26
GCC version: 4.7.3
*/

#include "../include/util.h"
#include <string>

using namespace std;

void split(const string &src, const string &separator, vector<string>& dest_list) {
    size_t pre_pos = 0, position;
    string temp = "";
    dest_list.clear();
    if(src.empty())
        return;
    while((position = src.find(separator.c_str(), pre_pos)) != string::npos) {
        temp.assign(src, pre_pos, position - pre_pos);
        if(!temp.empty())
            dest_list.push_back(temp);
        pre_pos = position + separator.length();
    }
    temp.assign(src, pre_pos, src.length() - pre_pos);
    if(!temp.empty())
        dest_list.push_back(temp);
}

string &trim(string &line) {
    if(!line.empty()) {
        string empty_str = "\t\r\n ";
        line.erase(0, line.find_first_not_of(empty_str));
        line.erase(line.find_last_not_of(empty_str) + 1);
    }
    return line;
}

void string_replace(string &origin, const string &src, const string &tgt) {
    string::size_type pos = 0, srclen = src.size(),  dstlen = tgt.size();
    while((pos = origin.find(src, pos)) != string::npos) {
        origin.replace(pos, srclen, tgt);
        pos += dstlen;
    }
}
