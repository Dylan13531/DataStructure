/*************************************************************************
    > File Name: testBST.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 一  2/24 13:58:07 2020
 ************************************************************************/

#include"binST.h"
#include <iostream>
using namespace std;

int main()
{
	BST<int> T1;
	T1.insert(19);
	cout << "T1->root: " << (T1.root())->data << endl;
	T1.insert(20);
	T1.insert(30);
	T1.insert(15);
	cout << "T1.search(20) :" << T1.search(20)->data << endl;
	T1.remove(20);
	cout << "root->rc: " << (T1.root()->rc->data) << endl;
	
	return 0;
}
