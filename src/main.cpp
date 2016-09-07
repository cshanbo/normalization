//coding:utf-8
/*
Program: test
Description: 
Date: 2016-07-05 21:07:39
Last modified: 2016-09-06 22:07:46
GCC version: 4.7.3
*/

#include <iostream>
#include <string>
#include <pcrecpp.h>

using namespace std;

int main() {
   int i;
   string s;
   pcrecpp::RE re("(\\w+):(\\d+)");
   if (re.error().length() > 0) {
	  cout << "PCRE compilation failed with error: " << re.error() << "\n";
   }
   if (re.PartialMatch("root:1234", &s, &i))
   cout << s << " : " << i << "\n";
}
