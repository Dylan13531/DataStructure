/*************************************************************************
    > File Name: myVector.h
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 五  2/ 7 15:30:04 2020
 ************************************************************************/
// c++ 中带template 的类声明和函数定义必须放在同一文件中

#ifndef MYVECTOR_H_
#define MYVECTOR_H_

namespace MyVector{
	typedef int Rank;
	const int DEFAULT_CAPACITY = 3;
	template <typename T>
	class Vector{
		private:
			Rank _size;
			int _capacity;
			T * _elem;
		protected:
			void copyFrom(T const * A, Rank lo, Rank hi);		//仅在构造函数中使用
			void expand();
			void shrink();
//			bool bubble(Rank lo, Rank hi);
//			void bubbleSort(Rank lo, Rank hi);
//			Rank max(Rank lo, Rank hi);
//			void selectionSort(Rank lo, Rank hi);
//			void merge(Rank lo, Rank mi, Rank hi);
//			void mergeSort(Rank lo, Rank hi);
//			Rank partition(Rank lo, Rank hi);
//			void quickSort(Rank lo, Rank hi);
//			void heapSort(Rank lo, Rank hi);
		public:
			Vector(int c=DEFAULT_CAPACITY, int s=0,T v=0)
			{
				_elem = new T [_capacity=c];
				for (_size=0; _size<s; _elem[_size++]=v);
			}
			Vector(T const * A, Rank n)
			{
				copyFrom(A,0,n);
			}
			Vector(T const * A, Rank lo, Rank hi)
			{
				copyFrom(A,lo,hi);
			}
			Vector(Vector<T> const & v){copyFrom(v._elem, 0, v._size);}
			Vector(Vector<T> const & v,Rank lo, Rank hi){copyFrom(v._elem, lo, hi);}
			~Vector(){ delete [] _elem;}
			Rank size() const { return _size;}
			bool empty() const { return _size==0;}
			int disordered() const;
			Rank find(T const & e) const {return find(e,0,_size);}
			Rank find(T const & e, Rank lo, Rank hi) const;
//			Rank search(T const & e) const {return (0 >= _size)? -1:search(e, 0, _size);}
//			Rank search(T const & e, Rank lo, Rank hi) const;
			const T & operator[](Rank r) const { return  _elem[r]; }
			T & operator[](Rank r) { return  _elem[r]; }
			Vector<T> & operator=(Vector<T> const & );
			T remove (Rank r);
			int remove(Rank lo, Rank hi);
			Rank insert(T const & e) {return insert(_size, e);}
			Rank insert(Rank r, T const & e);
//			void sort(Rank lo, Rank hi);
//			void sort(){sort(0, _size);}
//			void unsort(Rank lo, Rank hi);
//			void unsort() {unsort(0, _size);}
			int deduplicate();
			int uniquify_lo();
			int uniquify_hi();

			void traverse(void(*)(T &));
			template <typename VST>
			void traverse(VST & );
	};
//函数实现
	template <typename T>
	int Vector<T>::uniquify_lo()
	{
		int i=1;
		int old_size = _size;
		while(i < _size)
		{
			_elem[i-1] == _elem[i] ? remove(i-1):i++;
		}
		return old_size-_size;
	}

	template <typename T>
	int Vector<T>::uniquify_hi()
	{
		int i=0;
		int j=0;
		while(++j < _size)
		{
			if(_elem[i] != _elem[j])
				_elem[++i] = _elem[j];
		}
		_size = ++i;
		shrink();
		return j-i;
	}
	

	template <typename T>
	void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
	{
		_elem = new T [_capacity=2*(hi-lo)];
		_size = 0;
		for(; lo < hi; _elem[_size++] = A[lo++]);
	}

	template <typename T>
	void Vector<T>::expand()
	{
		if (_size < _capacity)
			return;
		if (_capacity < DEFAULT_CAPACITY)
			_capacity = DEFAULT_CAPACITY;
		T * oldElm = _elem;
		_elem = new T [_capacity <<= 1];
		for (int i=0; i<_size; i++)
			_elem[i] = oldElm[i];
		delete [] oldElm;
	}

	template <typename T>
	void Vector<T>::shrink()
	{
		if (_capacity < DEFAULT_CAPACITY << 1) return;
		if (_size > _capacity>>2) return;
		T * oldElm = _elem;
		_elem = new T [_capacity >>= 1];
		for (int i=0; i<_size; i++)
			_elem[i] = oldElm[i];
		delete [] oldElm;
	}

	template <typename T>
	Rank Vector<T>::find(T const & e, Rank lo, Rank hi) const
	{
		while ((hi-- > lo)&&(_elem[hi] != e));
		return hi;
	}

	template <typename T>
	Vector<T> & Vector<T>::operator=(Vector<T> const & v)
	{
		if (*this == v)
			return *this;
		if (_elem)
			delete [] _elem;
		copy(v._elem,0,v._size);
		return *this;
	}
	
	template <typename T>
	int Vector<T>::remove(Rank lo, Rank hi)
	{
		if (lo == hi)
			return 0;
		while(hi < _size)
			_elem[lo++] = _elem[hi++];
		_size = lo;
		shrink();
		return hi-lo;
	}

	template <typename T>
	T Vector<T>::remove(Rank r)
	{
		T e = _elem[r];
		remove(r,r+1);
		return e;
	}

	template <typename T>
	Rank Vector<T>::insert(Rank r, T const & e)
	{
		expand();
		for (int i=_size; i>r; i--)
			_elem[i] = _elem[i-1];
		_elem[r] = e;
		_size++;
		return r;
	}

	template <typename T>
	int Vector<T>::deduplicate()
	{
		int oldSize = _size;
		Rank i=1;
		while ( i < _size )
		{
			find(_elem[i],0,i) < 0?
				i++ : remove(i);
		}
		return oldSize - _size;
	}

	template <typename T>
	void Vector<T>::traverse(void(*visit)(T &))
	{
		for (int i=0; i<_size; i++)
			visit(_elem[i]);
	}

	template <typename T> 
		template <typename VST>
	void Vector<T>::traverse(VST & visit)
	{
		for (int i=0; i<_size; i++)
			visit(_elem[i]);
	}


	template <typename T>
	int Vector<T>::disordered() const
	{
		int n=0;
		for (int i=0; i<_size-1; i++)
		{
			if (_elem[i] > _elem[i+1])
				n++;
		}
		return n;
	}

	template <typename T>
	struct Increase
	{
		virtual void operator()(T &e){e++;}
	};
};



#endif

