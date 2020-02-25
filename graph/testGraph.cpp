/*************************************************************************
    > File Name: testGraph.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 三  2/19 16:02:27 2020
 ************************************************************************/

#include <iostream>
#include "graph.h"

using namespace std;
using namespace myGraph;

int main()
{
	GraphMatrix<int,int> test;
	test.insert(5);
	cout << "test.vertex 0: " << test.vertex(0) << endl;
	test.insert(6);
	cout << "test.vertex 1: " << test.vertex(1) << endl;
	test.insert(8);
	cout << "test.vertex 2: " << test.vertex(2) << endl;
	test.insert(9);
	cout << "test.vertex 3: " << test.vertex(3) << endl;
	test.insert(3);
	cout << "test.vertex 3: " << test.vertex(4) << endl;
	test.insert(1,1,0,1);
	test.insert(1,1,1,2);
	test.insert(1,1,3,2);
	test.insert(1,1,0,4);
	test.insert(1,1,4,3);
	cout <<"Indegree of vertex 2: " << test.inDegree(2) << endl;
	cout <<"Outdegree of vertex 0: " << test.outDegree(0) << endl;
	cout << "First neighbour of Vertex 0 : " << test.firstNbr(0) << endl;
	cout << "Next neighbour of Vertex 0 : " << test.nextNbr(0,3) << endl;
	cout << "Status of Vertex 0 : " << test.status(0) << endl;
	cout << "Number of Edge: " << test.e << endl;
	test.remove(4);
	cout << "Number of vertex : " << test.n << endl;
	cout << "Number of Edge: " << test.e << endl;
	cout << "Edge(0,1): " << test.edge(0,1) << endl;
	test.insert(3);
	cout << "test.vertex 3: " << test.vertex(4) << endl;
	test.insert(1,1,4,3);
	test.insert(1,1,4,1);
	test.remove(4,1);
	cout << "Number of Edge: " << test.e << endl;

	return 0;
}
