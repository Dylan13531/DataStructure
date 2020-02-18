/*************************************************************************
    > File Name: testNode.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 五  2/14 11:57:28 2020
 ************************************************************************/
#include "MyList.h"
#include <iostream>

int main()
{
	using namespace MyList;
	using namespace std;
//	ListNodePosi(double) header = new ListNode<double>;
//	ListNodePosi(double) trailer = new ListNode<double>;
//	header->succ = trailer;
//	trailer->prev = header;
//	cout << header->prev<< '\t' << trailer->succ << endl;
//	cout << header << '\t' << trailer->prev << endl;
//	cout << header->succ << '\t' << trailer << endl;
//	ListNodePosi(double) first = header->insertAsSucc(1);
//	
//	cout << "Inserting first: ";
//	cout << first << '\t' << header->succ << '\t' << trailer->prev << endl;
//	cout << header << '\t' << first -> prev << endl;
//	cout << trailer << '\t' << first->succ << endl;
//
//	cout << "Inserting last: ";
//	ListNodePosi(double) last = trailer->insertAsPred(2);
//	cout << last << '\t' << trailer->prev << '\t' << first->succ << endl;
//	cout << first << '\t' << last -> prev << endl;
//	cout << trailer << '\t' << last ->succ << endl;
//	trailer->insertAsPred(3);
//	ListNodePosi(double) pos = header;
//	for (int i=0; i<3; i++)
//		cout << (pos=pos->succ)->data << endl;
//	pos = pos->succ;
//	for (int i=0; i<3; i++)
//		cout << (pos=pos->prev)->data << endl;

	MyList::List<double> myList;
	cout << "Size of MyList is: " << myList.size()<< endl;
	if (myList.empty())
		cout << "MyList is empty!" << endl;
	myList.insertAsFirst(1);
	myList.insertAsLast(5);
	myList.insertA(myList.first(),2);
	myList.insertB(myList.last(),3);
	myList.insertB(myList.last(),4);
	cout << "Size of MyList is: " << myList.size()<< endl;
	cout << "First: " << myList.first()->data << endl;
	cout << "Last: " << myList.last()->data << endl;
	MyList::List<double> yourList(myList);
	cout << "Size of YourList is: " << yourList.size()<< endl;
	cout << "First: " << yourList.first()->data << endl;
	cout << "Last: " << yourList.last()->data << endl;
	MyList::List<double> list3(myList.first(),2);
	cout << "Size of List3 is: " << list3.size()<< endl;
	cout << "First: " << list3.first()->data << endl;
	cout << "Last: " << list3.last()->data << endl;
	MyList::List<double> list4(myList,2,2);
	cout << "Size of List4 is: " << list4.size()<< endl;
	cout << "First: " << list4.first()->data << endl;
	cout << "Last: " << list4.last()->data << endl;
	
	//test operator;
	myList.show();
	myList[4] = 10;
	myList.show();
	//test remove;
	
	cout << "Remove4: " << list4.remove(list4.first()) << endl;
	cout << "Size of List4 is: " << list4.size()<< endl;
	cout << "First: " << list4.first()->data << endl;
	cout << "Last: " << list4.last()->data << endl;
	cout << "disorder of List4: " << list4.disordered() << endl;
	myList[3] = 9;
	myList.insertAsLast(9);
	myList.show();
	cout << "disorder of myList: " << myList.disordered() << endl;
	cout << "find 9 in myList: " << myList.find(9)->data << endl;
	cout << "search 5: " <<(myList.search(5))->data << endl;
	cout << "select max: " << (myList.selectMax(myList.first(),4))->data<<endl;
	for (int i=0; i<myList.size(); i++)
	{
		myList[i] = 20-3*i;
	}
	myList.show();
	cout << "select max: " << (myList.selectMax(myList.first(),4))->data<<endl;
	myList.sort();
	myList.show();
	for (int i=0; i<myList.size(); i++)
	{
		myList[i] = 20-3*i;
	}
	myList.show();
	cout << "Reverse:" << endl;
	myList.reverse();
	myList.show();
	for (int i=0; i<myList.size(); i++)
	{
		myList[i] = 20;
	}
	myList.show();
//	myList.deduplicate();
	myList.traverse(MyList::plus2);
	myList.show();
	MyList::objPlus(myList);
	myList.show();

	return 0;
}
