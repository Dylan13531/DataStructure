/*************************************************************************
    > File Name: testMV.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 日  2/ 9 23:32:15 2020
 ************************************************************************/

#include "myVector.h"
#include <iostream>

int main()
{
	using namespace MyVector;
	using std::cout;
	using std::cin;
	using std::endl;
	Vector<int> testv1;
	for (int i=0; i<100; i++)
		testv1.insert(i);
	cout <<  "testv1.size: " << testv1.size() << endl;
	testv1.insert(3,5);
	int c = testv1[3];
	cout << "test[3]: " << c << endl;
	c = 8;
	cout << "test[3]: " << testv1[3] << endl;
	int a[10] = {5,6,7,8,9,10,11,12,13,14};
	Vector<int> testv2(a,4,9);
	cout << "testv2.size: " << testv2.size() << endl;
	int disod = testv2.disordered();
	cout << "disorder: " << disod << endl;
	int b[10] = {5,6,5,8,6,10,11,10,13,14};
	Vector<int> testv3(b,10);
	cout << "Deduplacate draw num: " << testv3.deduplicate()<< endl;
	int d[10] = {5,6,6,8,9,10,10,10,13,14};
	Vector<int> testv4(d,10);
	cout << "Order unquify by low Version,drop num: " << testv4.uniquify_lo() << endl;
	cout << "Order unquify by hi Version,drop num: " << testv4.uniquify_hi() << endl;
	int e[10] = {5,6,6,8,9,10,10,10,13,14};
	Vector<int> testv5(e,10);
	cout << "Find 4(should be -1)" << testv5.search(4)<<endl;
	cout << "Find 15(should be 10)" << testv5.search(15)<<endl;
	cout << "Find 6(should be ?)" << testv5.search(6)<<endl;
	cout << "Find 8(should be ?)" << testv5.search(8)<<endl;
	testv3.sort();
	testv3.show();

return 0;
}
