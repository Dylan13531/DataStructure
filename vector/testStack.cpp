/*************************************************************************
    > File Name: testStack.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 日  2/16 13:26:55 2020
 ************************************************************************/

#include <iostream>
#include "stack.h"
#include <cstring>

int main()
{
	using std::cout;
	using std::endl;
	void baseConversion(long,int);
	MyVector::stack<int> st1;
	cout << "size of st1: " << st1.size() << endl;
	st1.push(9);
	cout << "size of st1: " << st1.size() << endl;
	cout << "top of st1: " << st1.top() << endl;
	cout << "Base Conversion of 28 -> 2: " ;
	baseConversion(28,2);
	cout << endl;
	cout << "Testing Stach washing " << endl;
	if (stackWash("abcd","dcb"))
		cout << "washing success!" << endl;
	char test[] = "3+{4-[3*4/(2+4)-1]-3} + (2-3)=";
	cout << "Testing brace:" << test << endl; 
	if (paren(test,0,strlen(test)))
		cout << test << ": test pass!!"<<endl;
	else
		cout << test << ": test failed!!"<<endl;
	return 0;
}
