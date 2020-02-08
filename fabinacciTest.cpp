/*************************************************************************
    > File Name: fabinacciTest.h
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 五  2/ 7 17:48:21 2020
 ************************************************************************/

#include <iostream>

int fab(int n);
int fabIter(int n);
int main()
{
	int n;
	int method;
	std::cout << "Input n: ";
	std::cin >> n;
	std::cout << "Choose Method<1 or 2>: ";
	std::cin  >> method;
	int c;
	if (method == 1)
		c = fabIter(n);
	else
		c = fab(n);
	std::cout << "The result: " << c << std::endl;
	return 0;
}



int fab(int n)
{
	if (n < 2)
		return n;
	else
		return fab(n-1) + fab(n-2);
}

int fabIter(int n)
{
	int f,g;
	f = 0;
	g = 1;
	int i = 2;
	while (i++ <= n)
	{
		g = f + g;
		f = g -f;
	}
	return g;
}
