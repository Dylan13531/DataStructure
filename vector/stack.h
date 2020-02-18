/*************************************************************************
    > File Name: stack.h
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 日  2/16 13:20:08 2020
 ************************************************************************/
#ifndef _MyStack_H_
#define _MyStack_H_
#include "myVector.h"
#include <iostream>
#include <cstring>

using namespace std;
namespace MyVector
{
	template<typename T>
	class stack :public Vector<T>
	{
		public:
			void push(const T & e){this->insert(this-> size(),e);}			//c++模版类调用父类函数加this
			T pop() {return this->remove(this-> size()-1);}
//			T & top() { return this->operator[](this-> size()-1);}
			T & top() { return (*this)[this-> size()-1];}
	};
}

void  baseConversion(long num, int base)
{
	char digit[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	MyVector::stack<char> S;
	char *  result;
	S.push('\0');
	while (num >0)
	{
		S.push(digit[num%base]);
		num /= base;
	}
	result = new char [S.size()+1];
	for(int i=0; !S.empty();result[i++]=S.pop());
	cout << result;
	delete [] result;
}

bool stackWash(char *A, char*B)
{
	MyVector::stack<char> Sin;
	MyVector::stack<char> Smd;
	MyVector::stack<char> Sot;
	Smd.push('\n');
	int i=0;
	for(int i=0; i<strlen(A); Sin.push(A[i++]));
	while((!Sin.empty())||(Smd.top()==B[i]))
	{
		if ((!Sin.empty()) && (Sin.top() == B[i]))
		{
			i++;
			Sot.push(Sin.pop());
		}
		else if(Smd.top() == B[i])
		{
			Sot.push(Smd.pop());
			i++;
		}
		else
			Smd.push(Sin.pop());
		if (i == (strlen(B)-1))
			return true;
	}
	return false;
}

using namespace std;
bool paren( const char expr[] ,int lo, int hi)
{
	MyVector::stack<char> S;
	for(int i=lo; i<hi; i++)
	{
		switch(expr[i])
		{
			case '(': S.push(expr[i]); break;
			case '[': S.push(expr[i]); break;
			case '{': S.push(expr[i]); break;
			case ')': {
						  if((S.empty()) || (S.pop() != '(')) return false; 
						  break;
					  }
			case ']': {
						  if((S.empty()) || (S.pop() != '[')) return false; 
						  break;
					  }
			case '}': {
						  if((S.empty()) || (S.pop() != '{')) return false; 
						  break;
					  }
			default: break;
		}
	}
	return S.empty();
}


#endif
