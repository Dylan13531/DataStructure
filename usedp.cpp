/*************************************************************************
    > File Name: usedp.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 六  2/ 8 00:51:44 2020
 ************************************************************************/

#include "dp.h"


int main()
{
	StrNumCount test("tianicisnotgoog","wtianicisnotgooghatsthefuck");
	test.showStrA();
	test.showStrB();
	test.calLCS();
	test.showLCS();
//	test.showLCSdetail();
	return 0;
}
