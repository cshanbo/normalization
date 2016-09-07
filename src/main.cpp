//coding:utf-8
/*
Program: test
Description: 
Date: 2016-07-05 21:07:39
Last modified: 2016-09-07 11:09:04
GCC version: 4.7.3
*/

#include <iostream>
#include <fstream>
#include <string>
#include <pcrecpp.h>

#include "../include/util.h"

using namespace std;

int show_usage() {
    std::cout << "usage: cmd + input_file + result_file" << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        show_usage();
        exit(0);
    }

    string root_dir = "../conf";
    std::ifstream ifs(argv[1], std::ios::in);

    string line = "";
    while(ifs) {
        if(getline(ifs, line)) {
            trim(line);
            cout << line << endl;
        }
    }
    int i;
    string s;
    pcrecpp::RE re("(\\w+):(\\d+)");
    if (re.error().length() > 0) {
        std::cout << "PCRE compilation failed with error: " << re.error() << "\n";
    }
    if (re.PartialMatch("root:1234", &s, &i))
    std::cout << s << " : " << i << std::endl;
}
