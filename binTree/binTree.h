/*************************************************************************
    > File Name: binTree.h
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 一  2/17 13:05:23 2020
 ************************************************************************/
#ifndef _BINTREE_H_
#define _BINTREE_H_
#define sature(x) ((x)? (x)->height:-1)
#define max(a,b) ((a>b)? a:b)

#include "binNode.h"
template<typename T>
class BinTree
{
	protected:
		int _size;
		BinNodePosi(T) _root;
		virtual int updateHeight(BinNodePosi(T) x);
		void updateHeightAbove(BinNodePosi(T) x);
	public:
		BinTree():_size(0),_root(nullptr);
		~BinTree() {if (0 < _size):remove(_root);}
		int size() const{return _size;}
		bool empty() const{return !empty;}
		BinNodePosi(T) root{return _root;}
		BinNodePosi(T) insertAsRoot(T const  &e);
		BinNodePosi(T) insertAsLC(BinNodePosi(T) x,T const &e);
		BinNodePosi(T) insertAsRC(BinNodePosi(T) x,T const &e);
		BinNodePosi(T) attachAsLC(BinNodePosi(T) x,BinTree<T> * &T);
		BinNodePosi(T) attachAsRC(BinNodePosi(T) x,BinTree<T> * &T);
		int remove(BinNodePosi(T) x); //删除以x为节点的子树，并返回规模
		BinTree<T>* secede(BinNodePosi(T) x);//将子树删除并将其转化为独立子树
		template <typename VST>
		void travLevel(VST& visit) {if(_root) _root->travLevel(visit)}
		template <typename VST>
		void travPre(VST& visit) {if(_root) _root->travPre(visit)}
		template <typename VST>
		void travIn(VST& visit) {if(_root) _root->travIn(visit)}
		template <typename VST>
		void travPost(VST& visit) {if(_root) _root->travPost(visit)}
		bool operator<(BinTree<T> const & t)
		{ return (_root && t._root && (_root<t._root));}
		bool operator==(BinTree<T> const & t)
		{ return (_root && t._root && (_root==t._root));}
};

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height= 1+ max(stature(x->lc),stature(x->rc));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x);
{
	while(x)
	{
		updateHeight(x);
		x->x.parent;
	}
}


template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const & e)
{
	_size = 1;
	return _root = new BinNode<T> (e);
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x,T const &e)
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lc;
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x,T const &e)
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rc;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x,BinTree<T> * &S)
{
	if(x->lc = S->_root)
		x->lc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->root = nullptr;
	S->size = 0;
	release(S);
	S = nullptr;
	return x;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x,BinTree<T> * &S)
{
	if(x->rc = S->_root)
		x->rc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->root = nullptr;
	S->size = 0;
	release(S);
	S = nullptr;
	return x;
}

template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x) //删除以x为节点的子树，并返回规模
{
	FromParentTo(x) = nullptr;
	unpdateHeightAbove(x->parent);
	int n=removeAt(x);
	_size -= n;
	return n;
}

template<typename T>
static int removeAt(BinNodePosi(T) x)
{
	if(!x)
		return 0;
	int n = 1+removeAt(x->lc)+removeAt(x->rc);
	release(x->data);
	release(x);
	return n;
}
template<typename T>
BinTree<T>* secede(BinNodePosi(T) x) //将子树删除并将其转化为独立子树
{
	FromParentTo(x) = nullptr;
	updateHeightAbove(x->parent);
	BinTree<T>* S = new BinTree<T>;
	S->_root = x;
	x->parent = nullptr;
	S->_size = x.size();
	_size -= S->_size;
	return S;
}

#endif
