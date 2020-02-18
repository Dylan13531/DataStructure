/*************************************************************************
    > File Name: MyList.h
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 五  2/14 11:07:38 2020
 ************************************************************************/

#include <iostream>
#ifndef __MYLIST__H__
#define __MYLIST__H__
#define ListNodePosi(T)  ListNode<T>*

namespace MyList
{
	typedef int Rank;
	template <typename T>
	struct ListNode
	{
		T data;
		ListNode<T> * prev;
		ListNode<T> * succ;

		ListNode(){}; //针对header和trailed的构造函数
		ListNode(T e,  ListNodePosi(T) p=NULL, ListNodePosi(T) s=NULL):data(e),prev(p),succ(s){};
		ListNode(ListNodePosi(T) const & e):data(e->data),prev(e->prev),succ(e->succ){};
		ListNodePosi(T) insertAsPred(T const & e)
		{
			ListNodePosi(T) newNode = new ListNode<T>(e,prev,this);
			prev->succ = newNode;
			prev = newNode;
			return newNode;	
		}
		ListNodePosi(T) insertAsSucc(T const & e)
		{
			ListNodePosi(T) newNode = new ListNode<T>(e,this,succ);
			succ->prev = newNode;
			succ = newNode;
			return newNode;	
		}
	};

	template<typename T>
	class List
	{
		private:
			int _size;
			ListNodePosi(T) header;
			ListNodePosi(T) trailer;
		protected:
			void init();
			void copyNodes(ListNodePosi(T), int);
			int clear();
//			void merge(ListNodePosi(T)&,int, List<T> &,ListNodePosi(T), int);
//			void mergeSort(ListNodePosi(T)&, int);
			void selectionSort(ListNodePosi(T),int);
			void insertionSort(ListNodePosi(T),int);

		public:
			List(){init();}																			//
			List(List<T> const&L);
			List(List<T> const&L, Rank r, int n);
			List(ListNodePosi(T) p, int n);
			~List();
			Rank size() const {return _size;}														//
			bool empty() const {return _size<=0;}													//
			T& operator[](Rank r) const;
			T& operator[](Rank r);
			ListNodePosi(T) first() const {return header->succ;}									//
			ListNodePosi(T) last() const {return trailer->prev;}									//
			bool valid(ListNodePosi(T) p) {return p&&(header != p) && (trailer != p);}				//
			int disordered() const;
			ListNodePosi(T) find(T const & e) const {return find(e,_size,trailer);}					//
			ListNodePosi(T) find(T const & e,int n, ListNodePosi(T) p) const;
			ListNodePosi(T) search(T const& e) const {return search(e, _size, trailer);}			//
			ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
			ListNodePosi(T) selectMax(ListNodePosi(T) p, int n) const;
			ListNodePosi(T) selectMax() const {return selectMax(header->succ, _size);}						//
			ListNodePosi(T) insertAsFirst(T const & e) { _size++; return header->insertAsSucc(e);}	//
			ListNodePosi(T) insertAsLast(T const & e) { _size++; return trailer->insertAsPred(e);}	//
			ListNodePosi(T) insertA(ListNodePosi(T) p, T const & e) {_size++; return p->insertAsSucc(e);}	//
			ListNodePosi(T) insertB(ListNodePosi(T) p, T const & e) {_size++; return p->insertAsPred(e);}	//
			T remove(ListNodePosi(T) p);
			void show() const;
//			void merge(List<T> & L) {merge(first(), size, L, L.first(), L._size);}					//
			void sort(ListNodePosi(T) p, int n);
			void sort() {sort(first(), _size);}
			int deduplicate();
			int uniquify(){return deduplicate();}
			void reverse();

			void traverse(void(*) (T &));
			template <typename VST>
			void traverse(VST &);
	};

	template<typename T>
	int List<T>::deduplicate()
	{
		ListNodePosi(T) p = first();
		ListNodePosi(T) temp ;
		int i=1;
		int c;
		Rank oldSize = _size;
		while ( i<oldSize)
		{
			p = p->succ;
			temp = p;
			c = i;	
			while(c-- > 0)
			{
				 if((temp->prev)->data == p->data) 
				 {
					 remove(temp->prev);
					 break;
				 }
				 else
					 temp=temp->prev;
			}
			i++;
		}
		return oldSize-_size;
	}
				


	template<typename T>
	void List<T>::sort(ListNodePosi(T) p, int n)
	{
		std::cout << "sorting..." << std::endl;
//		selectionSort(p,n);
//		
		insertionSort(p,n);
	}

	template<typename T>
	void List<T>::init()
	{
		header = new ListNode<T>;
		trailer = new ListNode<T>;
		header->succ = trailer;
		header->prev = NULL;
		trailer->prev = header;
		trailer->succ = NULL;
		_size = 0;
	}

	template<typename T>
	void List<T>::copyNodes(ListNodePosi(T) p, int n)
	{
		init();
		while(n-- > 0) {insertAsLast(p->data); p=p->succ;}
	}

	template<typename T>
	List<T>::List(List<T> const&L)
	{
		copyNodes(L.first(),L._size);
	}

	template<typename T>
	List<T>::List(ListNodePosi(T) p, int n)
	{
		copyNodes(p,n);
	}

	template<typename T>
	List<T>::List(List<T> const&L, Rank r, int n)
	{
		ListNodePosi(T) temp= L.first();
		for (int i=0; i<r; i++)
			temp = temp->succ;
		copyNodes(temp, n);
	}


	template<typename T>
	T&List<T>::operator[](Rank r) const
	{
		ListNodePosi(T) temp= first();
		for (int i=0; i<r; i++)
			temp = temp->succ;
		return temp->data;
	}

	template<typename T>
	T&List<T>:: operator[](Rank r)
	{
		ListNodePosi(T) temp= first();
		for (int i=0; i<r; i++)
			temp = temp->succ;
		return temp->data;
	}

	template<typename T>
	T List<T>::remove(ListNodePosi(T) p)
	{
		p->prev->succ = p->succ;
		p->succ->prev = p->prev;
		T temp = p->data;
		delete p;
		_size--;
		return temp;
	}

	template<typename T>
	int List<T>::clear()
	{
		int oldSize = _size;
		while(_size > 0) remove(header->succ);
		return oldSize;
	}

	template<typename T>
	List<T>::~List()
	{
		clear();
		delete header;
		delete trailer;
	}

	template<typename T>
	int List<T>::disordered() const
	{
		int n=0;
		ListNodePosi(T) temp = first();
		for(int i=0; i<_size-1; i++)
		{
			if (temp->data > (temp->succ)->data)
				n++;

			temp = temp->succ;
		}
		return n;
	}

	template<typename T>
	ListNodePosi(T) List<T>::find(T const & e,int n, ListNodePosi(T) p) const
	{
		while(n > 0)
		{
			n = n-1;
			p = (p -> prev);

			if (p->data == e)
				return p;
		}
		return header;
	}

	template<typename T>
	ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const
	{
		while(n-- >= 0)
			if(((p = (p->prev)) -> data) <= e) break;
		return p;
	}
 
	template<typename T>
	ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) const
	{
		ListNodePosi(T)  maxNode(p);
		ListNodePosi(T) cur(p);
		while (n-- > 1)
		{
			if ((cur = cur-> succ) -> data >=  maxNode -> data)
				maxNode = cur; 
		}
		return maxNode;
	}

	template<typename T>
	void List<T>::selectionSort(ListNodePosi(T) p,int n)
	{
		ListNodePosi(T) head = p->prev;
		ListNodePosi(T) tail=p;
		ListNodePosi(T) maxNode;
		int temp = n;
		while (temp-- >0)
			tail = tail->succ;
		temp = n;
		while(temp > 1)
		{
			
			maxNode = selectMax(head->succ,temp);		//head 不能被移走
			insertB(tail,remove(maxNode));
			temp--;
			tail = tail->prev;
		}
	}

	template<typename T>
	void List<T>::insertionSort(ListNodePosi(T) p,int n)
	{
		ListNodePosi(T) insertNode;
		int t=0;
		while(t<n)
		{
			insertNode = search(p->data,t++,p);
			insertA(insertNode,p->data);
			p = p->succ;
			remove(p->prev);
		}
	}

	template<typename T>
	void List<T>::show() const
	{
		ListNodePosi(T) p = first();
		std::cout  << "Value: [";
		for (int i=1;i < _size+1; i++)
		{
			std::cout  << p->data << ", ";
			p = p->succ;
			if (i%10 == 0) 
			{
				std::cout<<std::endl;
				std::cout <<"\t";
			}
		}
		std::cout << '\b'<< '\b'<<']' << std::endl;
	}
	
	template<typename T>
	void List<T>::reverse() 
	{
		ListNodePosi(T) p = first();
		int n=_size;
		for(int i=0; i<n-1; i++)
			insertAsFirst(remove(p->succ));
	}

	template<typename T>
	void List<T>::traverse(void(* visit)(T &))
	{
		ListNodePosi(T) p=header;
		for(int i=0; i<_size;i++)
			visit((p=p->succ)->data);
	}

	template<typename T>
	void plus2(T & data)
	{
		data++;
	}

	template<typename T> template <typename VST>
	void List<T>::traverse(VST &visit)
	{
		ListNodePosi(T) p=header;
		for(int i=0; i<_size;i++)
			visit((p=p->succ)->data);
	}
	template<typename T>
	struct plus
	{
		void operator()(T& data){data++;}
	};

	template<typename T>
	void objPlus(List<T> & v)
	{
		plus<T> visit;
		v.traverse(visit);
	}


}


#endif
