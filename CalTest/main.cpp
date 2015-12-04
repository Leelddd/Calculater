#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include"Function.h"
#include"Calculater.h"
using namespace std;

void testFun() 
{
	Function f;
	vector<string> arg{ "a", "b", "c" };
	f.setArgVec(arg);
	f.addArgFun("a");
	f.addArgFun("b");
	f.addArgFun("c");
	f.addOper("+");
	f.addOper("+");
	vector<double> args{ 1, 2,3 };
	cout << f.callFunction(args);
	/*Function f;
	vector<string> arg{ "a", "b" };
	f.setArgVec(arg);
	f.addArgFun("a");
	f.addArgFun("b");
	f.addOper("+");
	vector<double> args{ 1, 2 };
	
	Function f2;
	vector<string> arg2{ "c", "d" };
	f2.setArgVec(arg2);
	f2.addArgFun("(c,d)");
	f2.addFunQue(&f);

	Function f3;
	vector<string> arg3{ "a", "b" };
	f3.setArgVec(arg3);
	f3.addArgFun("(a,b)");
	f3.addFunQue(&f2);
	cout << f3.callFunction(args);*/
	
}

int main()
{
	testFun();
	string codefile("function2.txt");
	Calculater cal(codefile);
	cout << cal.callMain();
	getchar();
}