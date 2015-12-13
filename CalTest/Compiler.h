//
//	declare of the class Compiler
//
//	analyze the code from the file and compiling functions to use
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

class Compiler{
public:
	Compiler() = default;
	Compiler(const string &filename);
	double callMain();
private:
	//entrance of the pragram
	Function main;
	
	//stored the Function
	map<string, Function> func_map;

	//store the basic operator
	set<char> basic_oper;

	//code
	string code;

	void getCode(const string &filename);

	//set basic operator
	void setBasicOper();

	void codeAnalysis();

	//divided the code by ';'
	void functionAnalysis(string &);

	//analysis the code of one function
	void formulaAnalysis(string &, Function&);
	void setMain(string & main_str);
};



#endif