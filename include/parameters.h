//coding:utf-8
/**********************************************
Program: Parameters for normalization
Description: 
Author: cshanbo@gmail.com
Date: 2016-09-07 13:34:29
Last modified: 2016-09-07 13:34:29
**********************************************/

#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#ifndef OVECTOR_SIZE
#define OVECTOR_SIZE 1200
#endif

#ifndef REGEX_RULE_COUNT
#define REGEX_RULE_COUNT 17
#endif

#ifndef MAX_TERM_COUNT
#define MAX_TERM_COUNT 40960
#endif

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

/*RecogObj存储识别结果和处理后的分词结果*/

typedef struct Recognition {
    std::string name;   //名称time_commont,
    std::string tag;    //tag 例如识别出为time_common类,tag可能是date time等
    int priority;       //优先级
    int span[2];        //左右index
    int confidence;     //confidence,目前是长度
    std::string content;    //内容
    std::unordered_map<std::string,std::string> result;   //string-->string 例如一项tag是date，有["year"] == 2008
    std::string context;        //上下文（前后先找符号，如果超过规定长度则停止）
    int context_span[2];        //上下文span
    std::string pos;        //postag未用
} RecogObj;

typedef struct SingleLineResult {
    std::string current_line;        //当前行字符串
    std::vector<std::string> unicode_string_list;   //按字分割list
    std::unordered_map<int, int> index_map;        //GB-->Unicode映射
    std::unordered_map<int, int> reversed_index_map;   //Unicode-->GB
    std::vector<RecogObj> word_list;    //分词后的list
    std::vector<RecogObj> result_list;  //识别结果list<RecogObj>
    std::unordered_map<std::string, int> feature_map;  //特征map, string-->int  string为OBJ的content加上一些标记，如"F-"等
    int end_index[REGEX_RULE_COUNT];    //每个规则识别出的end_index
    scw_out_t *pout;        //用词，存储分词之后的结果
    SingleLineResult()
    {
        for (int i = 0; i < REGEX_RULE_COUNT; ++i)
        {
            end_index[i] = -1;
        }
        pout = NULL;
        if((pout = scw_create_out(MAX_TERM_COUNT * 2, SCW_OUT_FLAG)) == NULL)
        {
            std::cerr << "error: initializing the output buffer error." << std::endl;
            return;
        }
    }
    int clear()
    {
        current_line = "";
        unicode_string_list.clear();
        index_map.clear();
        reversed_index_map.clear();
        word_list.clear();
        result_list.clear();
        feature_map.clear();
        for (int i = 0; i < REGEX_RULE_COUNT; ++i)
        {
            end_index[i] = -1;
        }
        return 0;
    }
    ~SingleLineResult()
    {
        clear();
        if (pout != NULL)
        {
            scw_destroy_out(pout);
            pout = NULL;

        }
    }
} SingleLineResult;

#endif
