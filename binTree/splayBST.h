/*************************************************************************
    > File Name: splayBST.h
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 二  2/25 14:03:55 2020
 ************************************************************************/

#include "binTree.h"

template<typename T>
class Splay:public BST<T>
{
	protected:
		BinNodePosi(T) splay(BinNodePosi(T) v);
	
	public:
		BinNodePosi(T) & search(const T& e);
		BinNodePosi(T) insert( const T& e);
		bool remove(const T &e);
}

template <typename NodePosi> inline
void attachAsLChild(NodePosi p, NodePosi lc)
{
	p->lc = lc;
	if(lc)
		lc->parent = p;
}

template <typename NodePosi> inline
void attachAsRChild(NodePosi p, NodePosi rc)
{
	p->rc = rc;
	if(lc)
		lc->parent = p;
}

template<typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)
{
	if (!v) return nullptr;
	BinNodePosi(T) p;
	BinNodePosi(T) g;
	p = v->parent;
	g = p->parent;
	while(p&&g)
	{
		BinNodePosi(T) gg = g->parent;
		if(IsLChild(*v))
		{
			if (IsLChild(*p))
			{
				attachAsLChild(g,p->lc);
				attachAsLChild(p,v->lc);
				attachAsRChild(p,g);
				attachAsRChild(v,p);
			}
			else
			{
				attachAsLChild(p,v->rc);
				attachAsRChild(g,v->lc);
				attachAsLChild(v,g);
				attachAsRChild(v,p);
			}
		}
		else
		{
			if (IsLChild(*p))
			{
				attachAsRChild(p,v->lc);
				attachAsLChild(g,v->rc);
				attachAsLChild(v,p);
				attachAsRChild(v,g);
			}
			else
			{
				attachAsRChild(g,p->lc);
				attachAsRChild(p,v->lc);
				attachAsLChild(p,g);
				attachAsLChild(v,p);
			}
		}
		if (!gg) v->parent = nullptr;
		else
			(g == gg->lc)? attachAsLChild(gg,v):attachAsRChild(gg,v);
		updateHeight(g);
		updateHeight(p);
		updateHeight(v);
		p = v->parent;
		g = p->parent;
	}
	p = v->parent;
	if (p)
	{
		if (IsLChild(*v))
		{
			attachAsLChild(p,v->rc);
			attachAsRChild(v,p);
		}
		else
		{
			attachAsRChild(p,v->lc);
			attachAsLChild(v,p);
		}
		updateHeight(p);
		updateHeight(v);
	}
	v->parent = nullptr;
	_root = v;
	return v;
}

template<typename T>
BinNodePosi(T) & Splay<T>::search(const T& e)
{
	BinNodePosi(T) p = searchIn(_root, e, _hot=nullptr);
	_root = splay(p? p:_hot);
	return _root;
}

template<typename T>
BinNodePosi(T) Splay<T>::insert(const T& e)
{
	if (!_root) {_size++; return _root = new BinNode<T>(e);}
	if (e == search(e)->data) return _root;
	_size++;
	BinNodePosi(T) t = _root;
	if (_root->data < e)
	{
		t->parent = _root = new BinNode<T>(e,nullptr,t,t->rc);
		if (HasRChild(*t))
		{
			t->rc->parent = _root;
			t->rc=nullptr;
		}
	}
	else
	{
		t->parent = _root = new BinNode<T>(e,nullptr,t->lc,t);
		if (HasLChild(*t))
		{
			t->lc->parent = _root;
			t->lc=nullptr;
		}
	}
	updateHeightAbove(t);
	return _root;
}


template<typename T>
bool Splay<T>::remove(const T& e)
{
	if(!_root || e!=search(e)->data) return false;
	BinNodePosi(T) w = _root;
	if (!HasLChild(*_root))
	{
		_root = _root->rc;
		if (_root) _root->parent = nullptr;
	}
	else if(!HasRChild(*_root))
	{
		_root = _root->lc;
		if (_root) _root->parent = nullptr;
	}
	else
	{
		BinNodePosi(T) lTree = _root->lc;
		lTree->parent = nullptr;
		_root->lc = nullptr;
		_root = _root->rc;
		_root->parent = nullptr;
		search(w->data);
		_root->lc = lTree;
		lTree->parent = _root;
	}
	size--;
	//delete w;
	if (_root)
		updateHeight(_root);
	return true;
}

