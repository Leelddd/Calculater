#include"stringAnalysis.h"

vector<string> split(const string &str, const string &separator){
	vector<string> strVec;
	string::size_type begin = 0, end = 0;
	while ((end = str.find(separator, begin)) != string::npos){
		strVec.push_back(str.substr(begin, end - begin));
		begin = ++end;
	}
	strVec.push_back(str.substr(begin));
	return strVec;
}

vector<string> splitSet(string str, const set<char> &basic_oper)
{
	vector<string> func_vec;
	auto begin = str.begin();
	auto iter_left = begin;
	auto iter_right = begin;
	while (iter_right != str.end())
	{
		if (basic_oper.find(*iter_right) != basic_oper.end())
		{
			func_vec.push_back(cutStr(iter_left, iter_right));
			iter_left = ++iter_right;
		}
		else
		{
			++iter_right;;
		}
	}
	func_vec.push_back(cutStr(iter_left, iter_right));
	return func_vec;
}

vector<string> findSet(string &str, const set<char> &basic_oper)
{
	vector<string> oper_vec;
	auto begin = str.begin();
	auto iter = str.begin();
	while (iter != str.end())
	{
		if (basic_oper.find(*iter) != basic_oper.end())
		{
			string s{ *iter };
			oper_vec.push_back(s);
		}
		else
		{
			;
		}
		++iter;
	}
	return oper_vec;
}

bool isNum(string &str)
{
	stringstream stream(str);
	double num = 0;
	char c;
	if (!(stream >> num))
		return false;
	if (stream >> c)
		return false;
	return true;
}

string::iterator find_count_of(string &str, const char c, const int n)
{
	int count = 0;
	auto iter = str.begin();
	while (iter != str.end())
	{
		if (*iter == c)
		{
			++count;
			if (count == n)
			{
				return iter;
			}
		}
		++iter;
	}
	return str.end();
}

string cutStr(string::iterator iter, string::iterator end)
{
	string str;
	while (iter != end)
	{
		str.insert(str.end(), *iter++);
	}
	return str;
}