/*************************************************************************
    > File Name: binST.h
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 日  2/23 16:31:24 2020
 ************************************************************************/

#ifndef BINTREE_H_
#define BINTREE_H_
#define Balanced(x) (sature((x).lc) == sature((x).rc))
#define BalFac(x) (sature((x).lc) - sature((x).rc))
#define AvlBalanced(x) ((-2<BalFac(x))&&(BalFac(x)<2))
#define tallerChild(x)(sature((x)->lc)>sature((x)->rc)?(x)->lc:(sature((x)->lc)<sature((x)->rc)?rc:(IsLChild(*(x))? x->lc:x->rc))

#include"binTree.h"
#include <iostream>
using namespace std;
template<typename T>
class BST:public BinTree<T>
{
	protected:
		BinNodePosi(T) _hot;
		BinNodePosi(T) connect34(
				BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
				BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),BinNodePosi(T));
		BinNodePosi(T) rotateAt(BinNodePosi(T) x);

	public:
		virtual BinNodePosi(T) & search(const T& e);
		virtual BinNodePosi(T) insert(const T& e);
		virtual bool remove(const T& e);
};

template<typename T>
class AVL:public BST<T>
{
	public:
		BinNodePosi(T) insert(const T& e);
		bool remove(const T &e);
};

template<typename T>
BinNodePosi(T) AVL<T>::insert(const T& e)
{
	BinNodePosi(T) &x = search(e);
	if(x) return x;
	BinNodePosi(T) &xx = new BinNode<T>(e,this->_hot);
	this->_size++;
	if (e < this->_hot->data) 
		this->_hot->lc = xx;
	else
		this->_hot->rc = xx;
	for(BinNodePosi(T) g=_hot;g;g=g->parent)
		if(!AvlBalanced(*g))
		{
			if (IsLChild(*g)) 
				g->parent->lc = rotateAt(tallerChild(tallerChild(g)));
			else 
				g->parent->rc =  rotateAt(tallerChild(tallerChild(g)));
			break;
		}
		else
			updateHeight(g);
	return xx;
}

template<typename T>
bool AVL<T>::remove(const T& e)
{
	BinNodePosi(T) &x = search(e);
	if(!x) return false;
	this->removeAt(x,_hot);
	this->_size--;
	for(BinNodePosi(T) g=_hot;g;g=g->parent)
		if(!AvlBalanced(*g))
		{
			if (IsLChild(*g)) 
				g->parent->lc = rotateAt(tallerChild(tallerChild(g)));
			else 
				g->parent->rc =  rotateAt(tallerChild(tallerChild(g)));
			updateHeight(g);
		}
	return true;

template<typename T>
BinNodePosi(T) & BST<T>::search(const T& e)
{
	return searchIn(this->_root, e, _hot=nullptr);
}

template<typename T>
BinNodePosi(T) & searchIn(BinNodePosi(T) & v,const T& e, BinNodePosi(T) & hot)
{
	if (!v || (e == v->data)) return v;
	hot = v;
	return searchIn(((e<v->data)? v->lc:v->rc),e,hot);
}

template<typename T>
BinNodePosi(T) BST<T>::insert(const T& e)
{
	if (!(this->_root))
		return this->insertAsRoot(e);
	BinNodePosi(T) s = search(e);
	if (s) return s;
	BinNodePosi(T) temp;
	temp = (e < _hot->data)? this->insertAsLC(_hot,e):this->insertAsRC(_hot,e);
	temp->parent = _hot;

	if (e < _hot->data)
		cout << "Insert  data at lc: " << temp->data << " of " << temp->parent->data  << endl;
	else
		cout << "Insert  data at rc: " << temp->data << " of " << temp->parent->data  << endl;

	return temp;
}

template<typename T>
BinNodePosi(T) BST<T>::connect34(
		BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
	a->lc = T0;
	a->rc = T1;
	if(T0) T0->parent = a;
	if(T1) T1->parent = a;
	updateHeight(a);
	c->lc = T2;
	c->rc = T3;
	if(T2) T2->parent = c;
	if(T3) T3->parent = c;
	updateHeight(c);
	b->lc = a;
	b->rc = c;
	a->parent = b;
	c->parent = b;
	updateHeightAbove(b);
	return b;
}

template<typename T>
BinNodePosi(T) BST<T>:: rotateAt(BinNodePosi(T) x)
{
	BinNodePosi(T) p = x->parent;
	BinNodePosi(T) g = p->parent;
	if IsLChild(*p)
		if IsLChild(*x)
		{
			p->parent = g->parent;
			return connect34(x,p,g,x->lc,x->rc,p->rc,g->rc);
		}
		else
		{
			x->parent = g->parent;
			return connect34(p,x,g,p->lc,x->lc,x->rc,g->rc);
		}
	else
		if IsLChild(*x)
		{
			x->parent = g->parent;
			return connect34(g,x,p,g->lc,x->lc,x->rc,p->rc);
		}
		else
		{
			p->parent = g->parent;
			return connect34(g,p,x,g->lc,p->lc,x->lc,x->rc);
		}
}

template<typename T>
bool BST<T>::remove(const T& e)
{
	BinNodePosi(T) s = search(e);
	if (!s) return false;
	removeAt(s,_hot); 
	(this->_size)--;
	this->updateHeightAbove(_hot);
	return true;
}

template<typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot)
{
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = nullptr;
	if(!HasLChild(*x))
	{
		IsLChild(*x) ? x->parent->lc:x->parent->rc = x->rc;
		succ = x->rc;
	}
	else if (!HasRChild(*x))
	{
		IsLChild(*x) ? x->parent->lc:x->parent->rc = x->lc;
		succ = x->lc;
	}
	else
	{
		w = w->succ();
		swap(x->data,w->data);
		BinNodePosi(T) u=w->parent;
		( (u==x)? u->rc:u->lc) = succ = w->rc;
	}
	hot = w->parent;
	if(succ)
		succ->parent = hot;
	return succ;
}

template<typename T>
void swap(T & a, T & b)
{
	T temp = a;
	a = b;
	b = temp;
}

	
#endif
