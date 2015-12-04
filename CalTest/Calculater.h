//
//	declare of the class Calculater
//
//	analyze the code from the file and create functions to use
//
//	2015/12/4	Leelddd


#ifndef CALCU_H
#define CALCU_H

#include"Function.h"
#include"stringAnalysis.h"
#include<fstream>
#include<map>
#include<set>
#include<string>
using namespace std;
class Function;

class Calculater{
public:
	Calculater() = default;
	Calculater(const string &filename);
	void addFunction(Function &fun);
	double callMain();
private:
	Function main;
	map<string, Function> func_map;
	set<char> basic_oper;
	string code;

	void setBasicOper();
	void analysisFuncStr(string &);
	void analysisFormula(string &, Function&);
};

double Calculater::callMain()
{
	return main.callFunction();
}

void Calculater::setBasicOper()
{
	vector<char> basic{ '+', '-', '*', '/', '^', '%' };
	for (auto c: basic)
		basic_oper.insert(c);
}

void Calculater::analysisFuncStr(string &fun_str)
{
	Function newFunc;
	auto begin = fun_str.begin();
	auto iter_left = begin;
	auto iter_right = begin;
	//if it is a function declare
	//first:	set the function name
	//second:	set the argument list
	//third:	set the computational formula
	if (fun_str.substr(0, 6) == "define")
	{
		iter_left += 6;
		iter_right = find_count_of(fun_str, '(', 1);
		newFunc.setName(cutStr(iter_left, iter_right));

		iter_left = find_count_of(fun_str, '(', 1)+1;
		iter_right = find_count_of(fun_str, ')', 1);
		newFunc.setArgVec(split(cutStr(iter_left, iter_right), ","));

		iter_left = find_count_of(fun_str, '(', 2) + 1;
		iter_right = fun_str.end()-1;
		analysisFormula(cutStr(iter_left, iter_right), newFunc);
		func_map[newFunc.getName()] = newFunc;
		/*vector<string> funs = splitSet(cutStr(iter_left, iter_right),basic_oper);
		for (auto s : funs)
		{
			if (s.find('(') == s.npos)
			{
				newFunc.addArgFun(s);
			}
			else
			{
				if (func_map.find(s.substr(0, s.find_first_of(')'))) != func_map.end())
				{
					newFunc.addArgFun(s.substr(s.find_first_of('('), s.size() - 1));
					newFunc.addFunQue(&func_map[s.substr(0, s.find_first_of('('))]);
				}
				else
				{
					cout << "some function has not been declare" << endl;
				}
			}
		}*/
	}
	else//it is the main function
	{
		vector<string> funs = splitSet(fun_str, basic_oper);
		for (string s : funs)
		{
			vector<string> arg_valstr = split(cutStr(find_count_of(s, '(', 1)+1, find_count_of(s, ')', 1)),",");
			vector<double> arg_val;
			for (string str : arg_valstr)
			{
				arg_val.push_back(stod(str));
			}
			Function *f = new Function(func_map[cutStr(s.begin(), find_count_of(s, '(', 1))].callFunction(arg_val));
			main.addFunction(f);
		}
		vector<string> opers = findSet(fun_str, basic_oper);
		main.setOper(opers);
	}
}

void Calculater::analysisFormula(string &str, Function &newFunc)
{
	vector<string> fun_vec = splitSet(str, basic_oper);
	vector<string> oper_vec = findSet(str, basic_oper);
	newFunc.setOper(oper_vec);
	for (auto s : fun_vec)
	{
		cout << "helllo" << s;
		if (s.find('(') == s.npos)
		{
			newFunc.addArgFun(s);
		}
		else// s is a function
		{
			if (func_map.find(s.substr(0, s.find_first_of('('))) != func_map.end())
			{
				newFunc.addArgFun(s.substr(s.find_first_of('('), s.size() - s.find_first_of('(')+1));
				newFunc.addFunQue(&func_map[s.substr(0, s.find_first_of('('))]);
			}
			else
			{
				cout << "some function has not been declare" << endl;
			}
		}
	}
}

Calculater::Calculater(const string &filename)
{
	setBasicOper();
	//get all the code
	ifstream in(filename);
	string buf;
	while (in >> buf)
	{
		code += buf;
	}
	//split the code by ";"
	vector<string> fun_string = split(code, ";");
	fun_string.pop_back();
	for (auto s: fun_string)
		analysisFuncStr(s);
}



#endif