/*************************************************************************
    > File Name: dp.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 五  2/ 7 21:10:01 2020
 ************************************************************************/
#ifndef DP_H_
#define DP_H_
#include <string>
#include <iostream>
/* 最长子序列问题*/

class StrNumCount
{
	private:
		enum {defaultLen=10};
		int lenA;
		int lenB;
		int numA;
		int numB;
		int numC;
		char *** countStr;				//记录i，j的最长公共子序列
		int ** lcsCount;				//记录i，j的最长公共子序列长度；
		char * strA;
		char * strB;
		int lcs;
	public:
		void setCountStr();

	public:
		StrNumCount(const char * ,const char *);
		StrNumCount();
		~StrNumCount();
		void showStrA() const{std::cout <<"A: " << strA << std::endl;}
		void showStrB() const{std::cout <<"B: " << strB << std::endl;}
		void showStrs() const{showStrA();showStrB();}
		void calLCS();
		void showLCSdetail();
		void showSingle(int a, int b);
		void showLCS(){showSingle(lenA,lenB);}

//		bool setStr(const char *, const char *);
//		bool setStrA(const char *);
//		bool setStrB(const char *);
};
		
#endif
