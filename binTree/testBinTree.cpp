/*************************************************************************
    > File Name: testBinTree.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 六  2/22 17:02:34 2020
 ************************************************************************/

#include "binTree.h"
#include <iostream>

int main()
{
	using namespace std;
	using namespace MyVector;
	Vector<BinNodePosi(int)> treeNodes;
	visitPlus<int> increase;
	BinTree<int> T;
	treeNodes.insert(T.insertAsRoot(23));
	cout << "The root value is: " << (T.root())->data << endl;
	for (int i=0; i<15; i++)
	{
		treeNodes.insert(T.insertAsLC(treeNodes[i],20+3*i));
		treeNodes.insert(T.insertAsRC(treeNodes[i],21+3*i));
	}
	cout << "The size of the Tree is: " << (T.size()) << endl;
	for (int i=0; i<treeNodes.size(); i++)
		cout << "The value of Nodes[" << i << "] is " << treeNodes[i]->data << endl;
	travIn_R1(treeNodes[0],increase);
	for (int i=0; i<treeNodes.size(); i++)
		cout << "The value of Nodes[" << i << "] is " << treeNodes[i]->data << endl;
	travIn_R2(treeNodes[0],increase);
	for (int i=0; i<treeNodes.size(); i++)
		cout << "The value of Nodes[" << i << "] is " << treeNodes[i]->data << endl;
	return 0;
}
