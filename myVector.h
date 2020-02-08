/*************************************************************************
    > File Name: myVector.h
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 五  2/ 7 15:30:04 2020
 ************************************************************************/

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
			void copyFrom(T const * A, Rank lo, Rank hi);
			void expand();
			void shrink();
			bool bubble(Rank lo, Rank hi);
			void bubbleSort(Rank lo, Rank hi);
			Rank max(Rank lo, Rank hi);
		public:
			Vector(int c=MyVector::DEFAULT_CAPACITY;int s=0;T v=0)
			{
				_elem = new T [_capacity=c];
				for (_size=0; _size<s;_elem[_size++]=v);
			}
			Vector(T const * A, Rank n)
			{
				copyFrom(A,0,n);
			}
			Vecotr(T const * A, Rank lo, Rank hi)
			{
				copyFrom(A,lo,hi);
			}


#endif

