/*************************************************************************
    > File Name: binNode.h
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 一  2/17 11:52:34 2020
 ************************************************************************/

#ifndef _binNode_H_
#define _binNode_H_
#define BinNodePosi(T) BinNode<T>*
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) ((HasLChild(x))||(HasRChild(x)))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

#define sibling(p) (IsLChild(*(p))? ((p)->parent->rc):(p)->parent->lc)
#define uncle(x) (IsLChild(*((x)->parent))? (x)->parent->parent->rc:(x)->parent->parent->lc)
#define FromParentTo(x) (IsRoot(x)? _root:(IsLChild(x)? (x).parent->lc:(x).parent->rc))

#include "../vector/stack.h"
#include "../List/queue.h"
typedef enum{RB_RED, RB_BLACK} RBColor;

template <typename T>
struct BinNode
{
		T data;
		BinNodePosi(T) parent;
		BinNodePosi(T) lc;
		BinNodePosi(T) rc;
		RBColor color;
		int height;
		int npl;

		BinNode():parent(nullptr),rc(nullptr),lc(nullptr),color(RB_RED),height(0),npl(1){}
		BinNode(T e,BinNodePosi(T) p=nullptr,BinNodePosi(T) lc=nullptr,
				BinNodePosi(T) rc=nullptr,RBColor c=RB_RED,int h=0,int l=1):data(e),
				parent(p),lc(lc),rc(rc),color(c),height(h),npl(l){}
		int size();
		BinNodePosi(T) insertAsLC(T const &);
		BinNodePosi(T) insertAsRC(T const &);
//		BinNodePosi(T) succ();
		template <typename VST> void travLevel(VST &);
		template <typename VST> void travPre(VST &);
		template <typename VST> void travIn(VST &);
		template <typename VST> void travPost(VST &);

		bool operator< (BinNode const & bn) {return data<bn.data;}
		bool operator==(BinNode const & bn) {return data==bn.data;}
};
template <typename T>
int BinNode<T>::size()
{
	int s = 1;
	if(lc) s+=lc->size();
	if(rc) s+=rc->size();
	return s;
}

template <typename T> template <typename VST> 
void BinNode<T>::travLevel(VST & visit)
{
	travLevelR<T,VST>(this, visit);
}

template <typename T> template <typename VST> 
void BinNode<T>::travPre(VST & visit)
{
	switch(rand() %3)
	{
		case 0:travPre_R1(this,visit); break;
		case 1:travPre_R2(this,visit); break;
		case 2:travPre_R3(this,visit); break;
		default: break;
	}
}

template <typename T> template <typename VST> 
void BinNode<T>::travIn(VST & visit)
{
	switch(rand() %3)
	{
		case 0:travIn_R1(this,visit); break;
		case 1:travIn_R2(this,visit); break;
		case 2:travIn_R3(this,visit); break;
		default: break;
	}
}

template <typename T> template <typename VST> 
void BinNode<T>::travPost(VST & visit)
{
	switch(rand() %2)
	{
		case 0:travPost_R1(this,visit); break;
		case 1:travPost_R2(this,visit); break;
		default: break;
	}
}
	
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const & e)
{
	lc = new BinNode (e,this);
	return lc;
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const & e)
{
	rc = new BinNode (e,this);
	return rc;
}

template<typename T> template<typename VST>			//先序遍历v1
void travPre_R1(BinNodePosi(T) x,VST & visit)
{
	if (!x)
		return;
	visit(x->data);
	travPre(x->lc,visit);
	travPre(x->rc,visit);
}

//先序遍历v2
template<typename T> template<typename VST>
void travPre_R2(BinNodePosi(T) x, VST & visit)
{
	MyVector::stack<BinNodePosi(T)> S;
	S.push(x);
	while(!S.empty())
	{
		x = S.pop();
		if (x)
		{
			visit(x->data);
			S.push(x->rc);
			S.push(x->lc);
		}
	}
}

//先序遍历v3
template<typename T> template<typename VST>
void travPre_R3(BinNodePosi(T) x, VST & visit)
{
	MyVector::stack<BinNodePosi(T)> S;
	while (true)
	{
		while(x)
		{
			visit(x->data);
			S.push(x->rc);
			x = x->lc;
		}
		if (S.empty())
			break;
		x = S.pop();
	}
}

//中序遍历v1
template<typename T> template<typename VST>
void travIn_R1(BinNodePosi(T) x,VST & visit)
{
	if (!x)
		return;
	travIn_R1(x->lc,visit);
	visit(x->data);
	travIn_R1(x->rc,visit);
}

//中序遍历v2
template<typename T> template<typename VST>
void travIn_R2(BinNodePosi(T) x, VST & visit)
{
	MyVector::stack<BinNodePosi(T)> S;
	while(true)
	{
		while (x)
		{
			S.push(x);
			x = x->lc
		}
		if (S.empty())
			break;
		x = S.pop();
		visit(x->data);
		x = x->rc;
	}
}

//中序遍历v3
template<typename T> template<typename VST>
void travIn_R3(BinNodePosi(T) x, VST & visit)
{
	MyVector::stack<BinNodePosi(T)> S;
	while (true)
	{
		if (x)
		{
			visit(x->data);
			S.push(x->rc);
			x = x->lc;
		}
		else if (!S.empty())
		{
			x = S.pop();
			visit(x->data);
			x = x->rc;
		}
		else
			break;
	}
}

//后序遍历v1
template<typename T> template<typename VST>
void travPost_R1(BinNodePosi(T) x,VST & visit)
{
	if (!x)
		return;
	travPost_R1(x->lc,visit);
	travPost_R1(x->rc,visit);
	visit(x->data);
}

template<typename T> template<typename VST>
void travPost_R2(BinNodePosi(T) x,VST & visit)
{
	MyVector::stack<BinNodePosi(T)> S;
	BinNodePosi(T) temp;
	if (x)
		S.push(x);
	while(!S.empty())
	{
		if(S.top() != x->parent)
		{
			while(temp = S.top())
			{
				if (HasLChild(*temp))
				{
					if(HasRChild(*temp))
						S.push(temp->rc);
					S.push(temp->lc);
				}
				else
					S.push(x->rc);
			}
			S.pop();
		}
		x = S.pop();
		visit(x->data);
	}
}

template<typename T> template<typename VST>
void travLevelR(BinNodePosi(T) x, VST & visit)
{
	MyList::queuq Q;
	Q.enqueue(x);
	while(!Q.empty())
	{
		x = Q.dequeue();
		visit(x->data);
		if (x->lc)
			Q.equeue(x->lc);
		if (x->rc)
			Q.equeue(x->rc);
	}
}
		


#endif
