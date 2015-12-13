//
//	Declare of class Function
//
//	Every thing is function
//	
//	2015/12/3	Leelddd
//

#ifndef FUNCTION_H
#define FUNCTION_H

#include<iostream>
#include<map>
#include<vector>
#include<stack>
using namespace std;

class Function;
class Function{
public:
	//create a simple Function with a double value
	Function(const double &ans){ answer = ans; isSimpleFunc = true; setPriority(); }

	//create a Function named n
	Function(const string &n = "") :name(n){ setPriority(); }

	//add Function into this Function
	void addFunction(Function *fun){ fun_vector.push_back(fun); }
	void addFunction(double num){ fun_vector.push_back(&Function(num)); }
	//add argument of the function to set the computational formula
	void addArgFun(const string &arg){ argfun_vector.push_back(arg); }
	//add operator
	void addOper(const string &oper){ oper_vector.push_back(oper); }
	void addFunQue(Function *fun){ 
		Function *f = new Function(*fun);
		fun_deque.push_back(f); 
	}

	//set the argument list
	void setArgVec(const vector<string> &args){ arg_vector = args; }
	void setFun(const vector<Function*> &func){ fun_vector = func; }
	void setOper(const vector<string> &opers){ oper_vector = opers; }
	void setArgValue(const vector<double> &func);

	//function call
	double callFunction();
	double callFunction(vector<double> &arg_vector);

	void setName(const string &n){ name = n; }
	const string &getName(){ return name; }
	vector<string> getArgVec() {
		return arg_vector;
}

private:
	string name;
	string function;
	double answer;
	bool isSimpleFunc = false;

	//vector of the argument list
	vector<string> arg_vector;
	//map of the argument and its value
	map<string, double> arg_value;
	
	//store the expression
	vector<string> oper_vector;
	vector<string> argfun_vector;
	vector<Function*> fun_vector;
	deque<Function*> fun_deque;
	//help to get the answer
	stack<Function*> fun_stack;
	stack<string> oper_stack;
	map<string, int> basic_priority;

	//use oper_vector and num_vector to get the answer and set the answer of this function
	void setAnswer();
	//set the basic oper priority into a map
	void setPriority();

	//these three function help to get the answer from stack
	//using oper_vector and num_vector to push into stack and do calculate
	void putVectorToStack();
	//pop two top num and one top oper to call doCalculate() and get the answer
	void popStackToCal();
	//use two num and one basic oper to calculate a num and return
	double doCalculate(const double front_num, const double num, const string &oper);
};


#endif