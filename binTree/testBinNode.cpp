/*************************************************************************
    > File Name: testBinNode.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 一  2/17 17:35:26 2020
 ************************************************************************/

#include "binNode.h"
#include <iostream>
#define max(a,b) ((a > b) ? a:b)

int main()
{
	using namespace std;
	BinNode<int> c(5);
	if IsRoot(c)
		std::cout << "C is root" << endl;
	BinNodePosi(int) lcd = c.insertAsLC(2);
	if IsLChild(*lcd)
		std::cout << "LCD is left child" << endl;
	BinNodePosi(int) rcd = c.insertAsRC(9);
	BinNodePosi(int) gld = lcd->insertAsLC(1);
	lcd->insertAsRC(3);
	if IsRChild(*rcd)
		std::cout << "RCD is right child" << endl;
	if HasParent(*lcd)
		std::cout << "LCD has parent!" << endl;
	if HasLChild(c)
		std::cout << "C has left child! " << endl;
	if HasRChild(c)
		std::cout << "C has right child! " << endl;
	if HasChild(c)
		std::cout << "C has child! " << endl;
	if HasChild(*lcd)
		std::cout << "LCD has child! " << endl;
	if HasBothChild(c)
		std::cout << "C has both child! " << endl;
	if IsLeaf(*rcd)
		std::cout << "RCD is a leaf! " << endl;
	if (sibling(rcd))
		std::cout << "RCD has sibling! " << endl;
	if (sibling(lcd))
		std::cout << "LCD has sibling! " << endl;
	if (sibling(gld))
		std::cout << "GLD has sibling! " << endl;
	if (uncle(gld))
		std::cout << "GLD has uncle! " << endl;
	std::cout << "The size of C is : " << c.size() << endl;
	std::cout << "The size of GLD is : " << gld->size() << endl;
	std::cout << "Max in 2,3 is: " << max(2,3) << endl;
	return 0;
}
