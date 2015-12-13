#include"Compiler.h"
#include<assert.h>
Compiler::Compiler(const string &filename)
{
	setBasicOper();
	assert(!basic_oper.empty());//test
	getCode(filename);
	assert(!code.empty());//test
	codeAnalysis();
}

void Compiler::setBasicOper()
{
	vector<char> basic{ '+', '-', '*', '/', '^', '%' };
	for (auto c : basic)
		basic_oper.insert(c);
}

void Compiler::getCode(const string &filename)
{
	ifstream in(filename);
	string buf;
	while (in >> buf)
	{
		code += buf;
	}
}

void Compiler::codeAnalysis()
{
	vector<string> fun_string = split(code, ";");
	fun_string.pop_back();
	for (auto s : fun_string)
	{
		//function define
		if (s.substr(0, 6) == "define")
		{
			functionAnalysis(s.substr(6, s.size()-6));
		}
		//set main function
		else
		{
			setMain(s);
		}
	}
}

void Compiler::functionAnalysis(string &fun_str)
{
	assert(*fun_str.begin() != '('&&*(fun_str.end()-1) == ')');//assert the fun_str is legal
	Function newFunc;
	auto begin = fun_str.begin();
	auto iter_left = begin;
	auto iter_right = begin;

	//set name
	iter_right = find_count_of(fun_str, '(', 1);
	newFunc.setName(cutStr(iter_left, iter_right));
	//assert(*newFunc.getName().end() != ')');//name is legal

	//set argument list
	iter_left = find_count_of(fun_str, '(', 1) + 1;
	iter_right = find_count_of(fun_str, ')', 1);
	newFunc.setArgVec(split(cutStr(iter_left, iter_right), ","));

	//set the computational formula
	iter_left = find_count_of(fun_str, '(', 2) + 1;
	iter_right = fun_str.end() - 1;
	formulaAnalysis(cutStr(iter_left, iter_right), newFunc);

	//add the new Function to func_map
	if (func_map.find(newFunc.getName()) != func_map.end())
	{
		cout << "double define for function \"" << newFunc.getName() << "\"" << endl;
	}
	else
	{
		func_map[newFunc.getName()] = newFunc;
	}
}

void Compiler::formulaAnalysis(string &str, Function &newFunc)
{
	deque<Function> undefiners;
	vector<string> func_vec;
	vector<string> oper_vec;
	auto iter_left = str.begin();
	auto iter_right = iter_left;

	while (iter_right != str.end())
	{
		//basic_oper
		if (basic_oper.find(*iter_right) != basic_oper.end())
		{
			func_vec.push_back(cutStr(iter_left, iter_right));
			string oper;
			oper.push_back(*iter_right);
			oper_vec.push_back(oper);
			iter_left = ++iter_right;
		}
		//undefined function
		else if (*iter_right == '(' && iter_left==iter_right)
		{
			Function undefiner;
			undefiner.setArgVec(newFunc.getArgVec());
			while (*iter_right != ')')
				++iter_right;
			formulaAnalysis(cutStr(iter_left+1, iter_right), undefiner);
			undefiners.push_back(undefiner);
			//get the newFunc's argument list, like(a,b)
			string argstring;
			argstring.push_back('(');
			for (auto s : newFunc.getArgVec())
			{
				argstring.append(s);
				argstring.push_back(',');
			}
			argstring.pop_back();
			argstring.push_back(')');
			func_vec.push_back(argstring);
			
			if (++iter_right != str.end()) {
				string oper;
				oper.push_back(*iter_right);
				assert(oper.size() == 1); 
				oper_vec.push_back(oper);
				iter_left = ++iter_right;
			}
			else {
				iter_left = iter_right;
			}
		}
		else
		{
			++iter_right;;
		}
	}
	if(iter_left!=iter_right)
		func_vec.push_back(cutStr(iter_left, iter_right));

	newFunc.setOper(oper_vec);
	for (auto s : func_vec)
	{
		if (s.find('(') == s.npos)
		{
			newFunc.addArgFun(s);
		}
		else// s is a function
		{
			if (*s.begin() == '(')
			{
				newFunc.addArgFun(s);
				newFunc.addFunQue(&undefiners.front());
				undefiners.pop_front();
			}
			else if (func_map.find(s.substr(0, s.find_first_of('('))) != func_map.end())
			{
				newFunc.addArgFun(s.substr(s.find_first_of('('), s.size() - s.find_first_of('(') + 1));
				newFunc.addFunQue(&func_map[s.substr(0, s.find_first_of('('))]);
			}
			else
			{
				cout << "function " << s << " has not been declare" << endl;
			}
		}
	}
}

void Compiler::setMain(string &main_str)
{
	vector<string> funs = splitSet(main_str, basic_oper);
	for (string s : funs)
	{
		vector<string> arg_valstr = split(cutStr(find_count_of(s, '(', 1) + 1, find_count_of(s, ')', 1)), ",");
		vector<double> arg_val;
		for (string str : arg_valstr)
		{
			arg_val.push_back(stod(str));
		}
		Function *f = new Function(func_map[cutStr(s.begin(), find_count_of(s, '(', 1))].callFunction(arg_val));
		main.addFunction(f);
	}
	vector<string> opers = findSet(main_str, basic_oper);
	main.setOper(opers);
}
 
double Compiler::callMain()
{
	return main.callFunction();
}