/*************************************************************************
    > File Name: maxDivid.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 日  2/ 9 13:40:56 2020
 ************************************************************************/
#include <iostream>
template<typename T>
void max2(T * a, int low, int hi, int & x1, int & x2);

int main()
{
	int a[10] = {94,23,52,82,41,33,41,21,32,98};
	int m1,m2;
	max2<int>(a,0,9,m1,m2);
	std::cout << "Max1: "<< m1 << ", Max2: " << m2 << std::endl;
	return 0;
}

template<typename T>
void max2(T * a, int low, int hi, int & m1, int & m2)
{
	if(hi-low == 1)
	{
		m1 =  (a[low] > a[hi])? a[low]:a[hi];
		return;
	}

	if(hi-low == 2)
	{
		if (a[hi] > a[hi-1])
		{
			if (a[hi] > a[low])
			{
				m1 = a[hi];
				m2 = (a[hi-1] > a[low])? a[hi-1]:a[low];
			}
			else
			{
				m1 = a[low];
				m2 = a[hi];
			}
		}
		else
		{
			if (a[hi-1] > a[low])
			{
				m1 = a[hi-1];
				m2 = (a[low] > a[hi])? a[low]:a[hi];
			}
			else
			{
				m1 = a[low];
				m2 = a[hi-1];
			}
		}
		return;
	}
	int mid = int((hi+low)/2);
	int x1L,x2L;
	max2(a, low, mid,x1L,x2L);
	int x1R,x2R;
	max2(a, mid+1, hi,x1R, x2R);
	if (x1L > x1R)
	{
		m1 = x1L;
		m2 = (x1R>x2L)? x1R:x2L;
	}
	else
	{
		m1 = x1R;
		m2 = (x1L > x2R)? x1L:x2R;
	}
	return;
}
