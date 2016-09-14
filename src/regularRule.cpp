//coding:utf-8
/***********************************************************
Program: Regular expression rules cpp
Description: 
Shanbo Cheng: cshanbo@gmail.com
Date: 2016-09-08 16:20:03
Last modified: 2016-09-09 19:53:13
GCC version: 4.9.3
***********************************************************/

#include <iostream>

#include "../include/util.h"
#include "../include/regularRule.h"
#include "../include/parameters.h"

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

    int err_offset = 0;
    const char* err;
    this->_re = pcre_compile(this->_re_str.c_str(), PCRE_CASELESS | PCRE_MULTILINE, &err, &err_offset,  NULL);

    if(!_re) {
        std::cerr << "pcre error [offset: " << err_offset << "] [err: " << err << "]" << std::endl;
        return -1;
    }
    return 0;
}


int RegularRule::analysisPattern(const std::string pattern) {
    // if(!_re)
    //     return -1;
    // int ovectorsize = OVECTOR_SIZE;
    // int ovector[OVECTOR_SIZE];
    // int length = slr.
    // return 0;
    const char* err;
    int err_offset = 0;
    this->_re = pcre_compile(pattern.c_str(), PCRE_CASELESS | PCRE_MULTILINE, &err, &err_offset, NULL);

    if(!_re) {
        this->_re = pcre_compile(pattern.c_str(), PCRE_CASELESS | PCRE_MULTILINE, &err, &err_offset, NULL); 
        return -1;
    }
    return 0;
}


int RegularRule::recog(SingleLineResult &slr, std::vector<RecogObj> &tmp_result_list) {           
    //RegularRule里的recog,在dm_recognizer里也有一个recog,调用该recog
    //用于识别正则,将结果放入tmp_result_list以便dm的recog使用
    if (this->_re == NULL)
        return -1;
    int ovectorsize = OVECTOR_SIZE;
    int ovector[OVECTOR_SIZE];
    const char *line = slr.current_line.c_str();
    int length = strlen(line);
    int startoffset = 0;
    int rc = 0;     //rc?
    do {
        rc = pcre_exec(this->_re, NULL, line, length, startoffset, PCRE_NOTEMPTY, ovector, ovectorsize);
        if(rc == 0)
            rc = ovectorsize/3;
        if(rc > 0) {
            startoffset = ovector[1];
            if (slr.index_map.find(ovector[0]) == slr.index_map.end() || slr.index_map.find(ovector[1]) == slr.index_map.end())
                continue;

            RecogObj ro;
            ro.name = RegularRule::_name;       //name
            ro.tag = RegularRule::_tag;     //tag
            ro.priority = RegularRule::_priority;
            ro.span[0] = ovector[0];
            ro.span[1] = ovector[1];

            ro.confidence = slr.index_map[ovector[1]] - slr.index_map[ovector[0]];
            getContext(ro, slr);       //获取上下文
            ro.content = slr.current_line.substr(ro.span[0], ro.span[1] - ro.span[0]);
            if (ro.tag == "date")
            {
                if (ro.span[1] < slr.current_line.size() && slr.current_line[ro.span[1]-1] >= 48 && slr.current_line[ro.span[1]-1] <= 57)
                {
                    if (slr.current_line[ro.span[1]] >= 48 && slr.current_line[ro.span[1]] <= 57)
                        continue;
                }
                else if (ro.span[0] > 0 && slr.current_line[ro.span[0]] >= 48 && slr.current_line[ro.span[0]] <= 57)
                {
                    if (slr.current_line[ro.span[0] - 1] >= 48 &&slr.current_line[ro.span[0] - 1] <= 57)
                        continue;
                }
            }
            if (ro.tag == "phone_number")
            {
                if (ro.span[0] > 0 && slr.current_line[ro.span[0] - 1] >= 48 && slr.current_line[ro.span[0] - 1] <= 57)
                    continue;
                if (ro.span[1] < slr.current_line.size() && slr.current_line[ro.span[1]] >= 48 && slr.current_line[ro.span[1]] <= 57)
                    continue;
            }
            int namecount = 0;
            pcre_fullinfo(RegularRule::_re, NULL, PCRE_INFO_NAMECOUNT, &namecount);

            if(namecount > 0)
            {
                unsigned char *nametable;
                pcre_fullinfo(RegularRule::_re, NULL, PCRE_INFO_NAMETABLE, &nametable);
                int entrysize;
                pcre_fullinfo(RegularRule::_re, NULL, PCRE_INFO_NAMEENTRYSIZE, &entrysize);
                for (int i = 0; i < namecount; ++i)
                {
                    char *table=(char*)(nametable + entrysize*i);
                    int pos=table[1]+(table[0]<<8);
                    string name_key(table+2);
                    string nameValue;
                    try{
                        //nameValue.assign(slr.current_line,ovector[2*pos],ovector[2*pos+1] - ovector[2*pos]);
                        nameValue = slr.current_line.substr(ovector[2*pos], ovector[2*pos+1] - ovector[2*pos]);
                    }catch(exception){
                        //cout << "inside regular_rule, namekey:" << name_key  << endl;
                        continue;
                        //break;
                    }
                    ro.result[name_key] = nameValue;        //?
                }
            }
            if (ro.tag == "num_pure")
            {
                if (ro.result.find("unit") != ro.result.end() || ro.result.find("unit_pre") != ro.result.end())
                    ro.tag = "num_with_unit";
                else
                {
                    if (ro.span[0] > ro.context_span[0] && ro.context[ro.span[0] - ro.context_span[0] - 1] == '.')
                        continue;
                    if (ro.span[1] < ro.context_span[1] && ro.context[ro.span[1] - ro.context_span[0]] == '.')
                        continue;
                    //if (ro.result["content"].size() > 1 && ro.result["content"][0] == '0' && ro.result["content"][1] != '.')
                    //    continue;
                }
            }
            tmp_result_list.push_back(ro);
        }

    } while(rc>0);
    
    return 0;
}
