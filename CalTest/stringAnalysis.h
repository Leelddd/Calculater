#ifndef STRING_H
#define STRING_H
#include<vector>
#include<string>
#include<iostream>
#include<sstream>
#include<set>
using namespace std;

vector<string> split(const string &str, const string &separator);

vector<string> splitSet(string str, const set<char> &basic_oper);

vector<string> findSet(string &str, const set<char> &basic_oper);

string::iterator find_count_of(string &str, const char c, const int n);

string cutStr(string::iterator iter, string::iterator end);

bool isNum(string &str);

#endif