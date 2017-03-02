//coding:utf-8
/**********************************************
Program: Normalization class cpp file
Description: 
Author: cshanbo@gmail.com
Date: 2016-09-08 09:42:43
Last modified: 2017-03-02 20:54:50
**********************************************/

#include <string>
#include "../include/regularRule.h"
#include "../include/recognizer.h"

Recognizer::Recognizer() {
    segmenter = NULL;
    _rule_list = NULL;
}

Recognizer::Recognizer(std::string DICT_PATH, std::string HMM_PATH, std::string USER_DICT_PATH, std::string conf_dir, bool use_segment, bool use_classifier) {
    segmenter = new cppjieba::Jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH);
    _rule_list = new RegularRule[REGEX_RULE_COUNT];
}

Recognizer::~Recognizer() {
    delete segmenter;
    delete[] _rule_list;
}

int Recognizer::readRegexRules(std::string conf_file) {
    std::ifstream ifs(conf_file.c_str(), std::ios::in); 
    if (!ifs) {
        std::cerr << "Regex configuration file doesn't exist: "<< conf_file << std::endl;
        return -1;
    }
    int i = 0;
    std::string input_line = "";

    while(ifs && i < REGEX_RULE_COUNT) {
        if(getline(ifs, input_line)) {
            if(input_line.empty())
                continue;
            if(input_line[0] == '#')
                continue;
            trim(input_line);
            this->_rule_list[i].analysis(input_line);
            this->_rule_list[i].setIndex(i);
            ++i;
        }
    }
    if (i != REGEX_RULE_COUNT) {
        cerr << "Rules number is less than REGEX_RULE_COUNT: " << conf_file << endl;
        exit(-1);
    }
    ifs.close();
    return 0;
}


void Recognizer::initRegexSet(std::string conf_file) {
    ifstream ifs(conf_file.c_str(), ios::in);
    if (!ifs) {
        cerr << "can't find regex configure set: " << conf_file + "/regex_set" << endl;
        exit(-1);
    }
    string input_line;
    string old_region = "";
    while(ifs) {
        if(getline(ifs, input_line)) {
            trim(input_line);
            if (input_line.empty())
                continue;
            if (input_line[0] == '[') {
                input_line = input_line.substr(1, input_line.size() - 2);
                // if (old_region != input_line)post_process_date_time
                //     old_region = input_line;
                continue;
            }
            vector<string> entry_list;
            split(input_line, "|", entry_list);
            // for (int i = 0; i < entry_list.size(); ++i)
            // {
            //     if (old_region == "REGION_DATE")
            //         this->_regex_date_set.insert(entry_list[i]);
            //     else if (old_region == "REGION_TIME")
            //         this->_regex_time_set.insert(entry_list[i]);
            //     else if (old_region == "REGION_NUM")
            //         this->_regex_num_set.insert(entry_list[i]);
            //     else if (old_region == "REGION_PHONE_IP")
            //         this->_regex_pi_set.insert(entry_list[i]);//pi是指phone number 和ip
            //     else if (old_region == "REGION_URL")
            //         this->_regex_url_set.insert(entry_list[i]);
            //     else if (old_region == "REGION_EMAIL")
            //         this->_regex_email_set.insert(entry_list[i]);
            // }

        }
    }
    ifs.close();

}

