/*************************************************************************
    > File Name: graph.h
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 三  2/19 14:17:47 2020
 ************************************************************************/

#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <limits.h>
#include <iostream>
#include "../vector/stack.h"
#include "../List/queue.h"
namespace myGraph
{
	typedef enum {UNDISCOVERED, DISCOVERED, VISITED} VStatus;
	typedef enum {UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} EType;

	using MyVector::stack;
	using MyVector::Vector;
	template<typename Tv, typename Te>
	class Graph
	{
		private:
			void reset()
			{
				for(int i=0; i<n; i++)					//vertex reset
				{
					status(i) = UNDISCOVERED;
					dTime(i) = fTime(i) = -1;
					parent(i) = 0;
					priority(i) = INT_MAX;
					for (int j=0; j<n; j++)
						if (exists(i,j)) 
							type(i,j) = UNDETERMINED;
				}
			}

			void BFS(int, int &);					//联通域广度优先算法
			void DFSStack(int v, int &clock)
			void DFS(int, int &);					//联通域深度优先算法
//			void BCC(int, int &, stack<int> &);		//联通域基于DFS的双联通分量分解算法
//			bool TSort(int, int &, stack<Tv> *);	//联通域基于DFS的拓扑排序算法	
//			template <typename PU> void PFS(int, PU);	//联通域优先级搜索框架	
		public:
			int n;
			virtual int insert(Tv const&) = 0;
			virtual Tv remove(int ) = 0;
			virtual Tv& vertex(int ) = 0;
			virtual int inDegree (int) = 0;
			virtual int outDegree(int) = 0;
			virtual int firstNbr(int) = 0;
			virtual int nextNbr(int, int) = 0;
			virtual VStatus & status(int) = 0;
			virtual int& dTime(int) = 0;
			virtual int& fTime(int) = 0;
			virtual int& parent(int) = 0;
			virtual int& priority(int) = 0;

			int e;
			virtual bool exists(int, int) = 0;
			virtual void insert(Te const &, int, int, int) = 0;
			virtual Te remove(int, int)=0;
			virtual EType& type(int, int)=0;
			virtual Te& edge(int, int)=0;
			virtual int& weight(int,int)=0;
			void bfs(int);
//			void dfs(int);
//			stack<Tv>* tSort(int);
//			void prim(int);
//			void dijkstra(int);
//			template<typename PU> void pfs(int, PU);
	};
	template<typename Tv, typename Te>
	void Graph<Tv,Te>::bfs(int s)
	{
		int clock = 0;
		int v = s;
		do
		{
			if (status(v) == UNDISCOVERED)
				BFS(v,clock); 
		}while(s != (v = (v++)%n));
	}

	template<typename Tv, typename Te>
	void Graph<Tv,Te>::dfs(int s)
	{
		int clock = 0;
		int v = s;
		do
		{
			if (status(v) == UNDISCOVERED)
				DFS(v,clock); 
		}while(s != (v = (v++)%n));
	}
	
	template<typename Tv, typename Te>
	void Graph<Tv,Te>::DFS(int v, int &clock)
	{
		status(v) = DISCOVERED;
		dTime(v) = ++clock;
		for(int u=firstNbr(v); -1 < u; u = nextNbr(v))
		{
			if (status(u) == UNDISCOVERED)
			{
				parent(u) = v;
				type(v,u) = TREE;
				DFS(u,clock);
			}
			else if(status(u) == DISCOVERED)
			{
				type(v,u) = BACKWARD;
			}
			else
				type(v,u) = (dTime(v) < dTime(u))? FORWARD:CROSS;
		}
		fTime(v) = ++clock;
		status(v) = VISITED;
	}

	template<typename Tv, typename Te>
	void Graph<Tv,Te>::DFSStack(int v, int &clock)
	{
		MyVector::stack<int> S;	
		status(v) = DISCOVERED;
		dTime(v) = ++clock;
		S.push(v);
		while(!S.empty())
		{
			v = S.pop();
			for(int u=firstNbr(v); -1 < u; u = nextNbr(v))
			{
				if (status(u) == UNDISCOVERED)
				{
					parent(u) = v;
					type(v,u) = TREE;
					S.push(u);
					status(u) = DISCOVERED;
					dTime(u) = ++clock;
				}
				else if(status(u) == DISCOVERED)
				{
					type(v,u) = BACKWARD;
				}
				else
					type(v,u) = CROSS;
			}
			fTime(v) = ++clock;
			status(v) = VISITED;
		}
	}

	template<typename Tv, typename Te>
	void Graph<Tv,Te>::BFS(int s, int &clock)
	{
		MyList::queue<int> Q;
		status(s) = DISCOVERED;
		Q.equeue(s);
		while(!Q.empty())
		{
			int v = Q.dequeue();	
			dTime(v) = ++clock;
			for (int u=firstNbr(v); -1<u; u=nextNbr(v))
			{
				if (status(u) == UNDISCOVERED)
				{
					status(u) = DISCOVERED;
					Q.equeue(u);
					type(v,u) = TREE;
					parent(u) = v;
				}
				else
				{
					type(v,u) = CROSS;
				}
			}
			staus(v) = VISITED;
			// something else;
		}
	}


	template <typename Tv>
	struct Vertex
	{
		Tv data;						//		数据
		int inDegree;					//		入度
		int outDegree;					//      出度	
		VStatus status;					//		状态
		int dTime;						//		时间标签
		int fTime;
		int parent;						//		遍历树的父节点	
		int priority;

		Vertex(Tv const& d = (Tv)0):data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}
	};

	template <typename Te>
	struct Edge
	{
		Te data;
		int weight;
		EType type;
		Edge(Te const& d, int w=1):data(d),weight(w),type(UNDETERMINED){}
	};


	template<typename Tv, typename Te>
	class GraphMatrix:public Graph<Tv,Te>
	{
		private:
			Vector<Vertex<Tv> > V;
			Vector<Vector<Edge<Te> * > > E;
		public:
			GraphMatrix()
			{
				this->n=this->e=0;

			}
			~GraphMatrix()
			{
				for (int i=0; i<this->n; i++)
					for(int j=0; j<this->n; j++)
						delete E[i][j];
			}

			virtual Tv & vertex(int i) {return V[i].data;}
			virtual int inDegree(int i) {return V[i].inDegree;}
			virtual int outDegree(int i) {return V[i].outDegree;}
			virtual int firstNbr(int i) {return nextNbr(i,this->n);}
			virtual int nextNbr(int i, int j) 
			{
				while( (-1<j) &&(!exists(i,--j))); 
				return j;
			}
			virtual VStatus& status(int i) {return V[i].status;}
			virtual int& dTime(int i) {return V[i].dTime;}
			virtual int& fTime(int i) {return V[i].fTime;}
			virtual int& parent(int i) {return V[i].parent;}
			virtual int& priority(int i) {return V[i].priority;}
			virtual int insert(Tv const & vertex)
			{
				for (int i=0; i<this->n; i++)
					E[i].insert(nullptr);
				this->n += 1;
				E.insert(Vector<Edge<Te>* >(this->n,nullptr));
				return V.insert(Vertex<Tv>(vertex));								//返回最后一个元素的秩
			}

			virtual Tv remove(int i)
			{
				for (int j=0; j<this->n; j++)
				{
					if (exists(i,j))
					{
						delete E[i][j];
						V[j].inDegree--;
						this->e-=1;
//						cout << "delete success(i->j) " << this->e << endl;	
					}
					E.remove(i);
				}
				for (int j=0; j<this->n; j++)
				{
					if (exists(j,i))
					{
						Edge<Te>* le = E[j].remove(i);
						delete le;
						V[j].outDegree--;
						(this->e) -=1;
//						cout << "delete success(j->i) " << this->e << endl;	
					}
				}
				V.remove(i);
				this->n -= 1;
				Tv vBak = vertex(i);
				return vBak;
			}

			virtual bool exists(int i, int j)
			{return ((i>=0)&(i<this->n)&(j>=0)&(j<this->n)&(E[i][j]!=nullptr));}
			virtual EType& type(int i, int j){return E[i][j]->type;}
			virtual Te& edge(int i, int j) {return E[i][j] ->data;}
			virtual int& weight(int i, int j){return E[i][j] -> weight;}
			virtual void insert(Te const& edge, int w, int i, int j)
			{
				if (exists(i,j))
					remove(i,j);
				E[i][j] = new Edge<Te>(edge, w);
				this->e++;
				V[i].outDegree++;
				V[j].inDegree++;
				return;
			}
			virtual Te remove(int i,int j)
			{
				Te eBak =edge(i,j);
				delete E[i][j];
				E[i][j] = nullptr;
				this->e --;
				V[i].outDegree --;
				V[j].inDegree --;
				return eBak;
			}
	};
}
#endif
