/*************************************************************************
    > File Name: testqueqe.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 日  2/16 16:40:02 2020
 ************************************************************************/
#include "queue.h"
#include<iostream>

int main()
{
	using namespace std;
	MyList::queue<int>  q1;
	cout << "The size of q1: " << q1.size() << endl;
	q1.enqueue(3);
	q1.enqueue(2);
	q1.enqueue(1);
	cout << "The size of q1: " << q1.size() << endl;
	cout << "Deque: " << q1.dequeue() << endl;
	return 0;
}
