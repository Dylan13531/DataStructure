/*************************************************************************
    > File Name: queue.h
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 日  2/16 16:34:11 2020
 ************************************************************************/

#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "MyList.h"


namespace MyList
{
	template<typename T>
	class queue : public List<T>
	{
		public:
			void enqueue(const T & e){ this->insertAsLast(e);}
			T dequeue() {return this->remove(this->first());}
			T & front() {return (this->first())->data;}
	};
}

#endif
