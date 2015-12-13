#include"Function.h"
#include"stringAnalysis.h"
#include<assert.h>
//public method of class Function

double Function::callFunction(vector<double> &arg)
{
	//link value list and arg list into arg_value(map)
	if (arg.size() < arg_vector.size())
	{
		cout << "you should put in more values to init the argument" << endl;
	}
	else
	{
		auto arg_iter = arg_vector.begin();
		auto value_iter = arg.begin();
		while (value_iter != arg.end())
		{
			arg_value[*arg_iter++] = *value_iter++;
		}
	}
	assert(arg_value.size() == arg_vector.size());//test
	
	//s:(a,b);a;1;	4 kinds of conditions
	for (auto s : argfun_vector)
	{
		//if just a argument, number or argument
		if (s.find_first_of('(') == s.npos)
		{
			Function *f;
			if (isNum(s))
			{
				f = new Function(stod(s));
			}
			else
			{
				f = new Function(arg_value[s]);
			}
			fun_vector.push_back(f);
		}
		//if s is a function 
		else
		{
			s.erase(s.begin());
			s.pop_back();
			vector<string> sub_func_arg = split(s, ",");
			vector<double> sub_func_arg_val;
			for (auto s : sub_func_arg)
			{
				if (isNum(s))
				{
					sub_func_arg_val.push_back(stod(s));
				}
				else
				{
					sub_func_arg_val.push_back(arg_value[s]);
				}	
			}
			fun_deque.front()->callFunction(sub_func_arg_val);
			fun_vector.push_back(fun_deque.front());
			fun_deque.pop_front();
		}
	}
	return callFunction();
}

double Function::callFunction(){
	
	if (!isSimpleFunc)
		setAnswer();
	return answer;
}

void Function::setAnswer()
{
	putVectorToStack();
	while (!oper_stack.empty())
		popStackToCal();
	answer = fun_stack.top()->callFunction();
	isSimpleFunc = true;
}

void Function::setArgValue(const vector<double> &func)
{
	auto func_iter = func.begin();
	auto arg_iter = argfun_vector.begin();
	while (arg_iter != argfun_vector.end())
	{
		arg_value[*arg_iter++] = *func_iter++;
	}
}

//private method of class Function

void Function::setPriority()
{
	basic_priority["+"] = 5;
	basic_priority["-"] = 5;
	basic_priority["*"] = 10;
	basic_priority["/"] = 10;
	basic_priority["^"] = 15;
	basic_priority["%"] = 7;
}

void functionAnalysis()
{
	//getName();//between 'define' and first '('
	//getAgr();//between first '()', and split by ','
	//getFunVector();//split by basic operator and get a vector, loop the vector, if iter is a num, push in vector, if iter is a function, find it in map
}

void Function::putVectorToStack()
{
	auto fun_iter = fun_vector.begin();
	auto oper_iter = oper_vector.begin();
	while (oper_iter != oper_vector.end())
	{
		fun_stack.push(*fun_iter++);
		if (oper_stack.empty())
			oper_stack.push(*oper_iter++);
		else if (basic_priority[*oper_iter] <= basic_priority[oper_stack.top()])
		{
			popStackToCal();
			oper_stack.push(*oper_iter++);
		}
		else
		{
			oper_stack.push(*oper_iter++);
		}
	}
	fun_stack.push(*fun_iter);
}

void Function::popStackToCal()
{
	double right_num = fun_stack.top()->callFunction();
	fun_stack.pop();
	double left_num = fun_stack.top()->callFunction();
	fun_stack.pop();
	string oper = oper_stack.top();
	oper_stack.pop();
	Function *f = new Function(doCalculate(left_num, right_num, oper));
	fun_stack.push(f);
}

double Function::doCalculate(const double left_num, const double right_num, const string &oper)
{
	if (oper == "+"){
		return right_num + left_num;
	}
	else if (oper == "-"){
		return left_num - right_num;
	}
	else if (oper == "*"){
		return right_num * left_num;
	}
	else if (oper == "/"){
		return left_num / right_num;
	}
	else if (oper == "^"){
		double answer = left_num;
		if (right_num == 0)	return 1;
		else if (right_num == 1)	return left_num;
		for (int i = 2; i <= right_num; i++){
			answer = answer * left_num;
		}
		return answer;
	}
	else if (oper == "%"){
		return (int)left_num % (int)right_num;
	}
	return 0;
}