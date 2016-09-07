//coding:utf-8
/*
Program: util.cpp basic functions
Description: 
Shanbo Cheng: cshanbo@gmail.com
Date: 2016-07-05 20:46:23
Last modified: 2016-09-07 16:16:01
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

int seg_words(SingleLineResult& slr, cppjieba::Jieba& segmenter) {
    // if(slr.pout.empty())
    //     return 0;
    char *line = const_cast<char *>(slr.current_line.c_str());
    int len = strlen(line);

    const char MAX_TERM_LENGTH = 50;
    char word[MAX_TERM_LENGTH];
    u_int pos = 0;
    u_int token_len = 0;
    
    std::vector<cppjieba::Word> jiebawords;
    segmenter.CutForSearch(slr.current_line, jiebawords, true);
    cout << jiebawords << endl;

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
