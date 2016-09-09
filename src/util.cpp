//coding:utf-8
/*
Program: util.cpp basic functions
Description: 
Shanbo Cheng: cshanbo@gmail.com
Date: 2016-07-05 20:46:23
Last modified: 2016-09-09 15:50:11
GCC version: 4.7.3
*/

#include <string>

#include "../include/util.h"

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

void stringReplace(string &origin, const string &src, const string &tgt) {
    string::size_type pos = 0, srclen = src.size(),  dstlen = tgt.size();
    while((pos = origin.find(src, pos)) != string::npos) {
        origin.replace(pos, srclen, tgt);
        pos += dstlen;
    }
}

int segWords(SingleLineResult& slr, cppjieba::Jieba& segmenter) {
    // if(slr.pout.empty())
    //     return 0;
    // char *line = const_cast<char *>(slr.current_line.c_str());
    int len = slr.current_line.length();

    const char MAX_TERM_LENGTH = 50;
    char word[MAX_TERM_LENGTH];
    u_int pos = 0;
    u_int token_len = 0;
    
    std::vector<cppjieba::Word> jiebawords;
    segmenter.CutForSearch(slr.current_line, jiebawords, true);

    for(auto item: jiebawords) {
        token_len = item.word.length();
        if(token_len > MAX_TERM_LENGTH)
            return -1;
        RecogObj ro;
        ro.tag = "wordseg";
        ro.span[0] = item.offset;
        ro.span[1] = ro.span[0] + token_len;
        ro.result["content"] = item.word;
        slr.word_list.push_back(ro);
    }

    // if(slr.pout->wsbtermcount > 0 )
    // {
    //     for(u_int i = 0; i < slr.pout->wsbtermcount; ++i)
    //     {
    //         pos = GET_TERM_POS(slr.pout->wsbtermpos[i]);
    //         token_len = GET_TERM_LEN(slr.pout->wsbtermpos[i]);
    //         if (token_len >= MAX_TERM_LENGTH)
    //             return -1;
    //         RecogObj ro;
    //         ro.tag = "wordseg";
    //         ro.span[0] = slr.pout->wsbtermoffsets[i];
    //         ro.span[1] = ro.span[0] + token_len;
    //         strncpy(word, slr.pout->wordsepbuf + pos, token_len);
    //         word[token_len] = 0;
    //         ro.result["content"] = word;
    //         slr.word_list.push_back(ro);
    //     }
    // }
    return 0;
}

int getContext(RecogObj &ro, SingleLineResult &slr) {
    assert (slr.index_map.find(ro.span[0]) != slr.index_map.end());
    assert (slr.index_map.find(ro.span[1]) != slr.index_map.end());
    int start_index = slr.index_map[ro.span[0]] - 1;
    int end_index = slr.index_map[ro.span[1]];
    if (start_index < 0)
        start_index = 0;
    if (end_index > slr.unicode_string_list.size())
        end_index = slr.unicode_string_list.size();
    int i = 0;
    while (start_index > 0) {
        if (splitterJudge(slr.unicode_string_list[start_index]) || i == CONTEXT_WINDOW) {
            ++start_index;
            break;
        }
        --start_index;
        ++i;
    }
    i = 0;
    while (end_index < slr.unicode_string_list.size()) {
        if (splitterJudge(slr.unicode_string_list[end_index]) || i == CONTEXT_WINDOW)
            break;
        ++end_index;
        ++i;
    }
    start_index = slr.reversed_index_map[start_index];
    end_index = slr.reversed_index_map[end_index];
    ro.context = slr.current_line.substr(start_index, end_index - start_index);
    ro.context_span[0] = start_index;
    ro.context_span[1] = end_index;
    return 0;
}

bool splitterJudge(std::string str) {
    if (str == "," or str == "，" or str == "。")
        return true;
    return false;
}
