#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include"Function.h"
#include"Compiler.h"
using namespace std;

void testFun() 
{
	//string codefile1("function.txt");
	//Compiler testCom1(codefile1);
	//cout << endl << testCom1.callMain();

	//string codefile2("function2.txt");
	//Compiler testCom2(codefile2);
	//cout << endl << testCom2.callMain();

	//string codefile3("function3.txt");
	//Compiler testCom3(codefile3);
	//cout << endl << testCom3.callMain();

	//string codefile4("function4.txt");
	//Compiler testCom4(codefile4);
	//cout << endl << testCom4.callMain();

	string codefile5("function5.txt");
	Compiler testCom5(codefile5);
	cout << endl << testCom5.callMain();
}

int main()
{
	testFun();
	getchar();
}