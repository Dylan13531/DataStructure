/*************************************************************************
    > File Name: dp.cpp
    > Author: DylanYang
    > Mail: 13162687569@163.com 
    > Created Time: 五  2/ 7 21:37:29 2020
 ************************************************************************/
#include "dp.h"
#include <iostream>
#include <cstring>

	
void StrNumCount::setCountStr()
{
	numA = (lenA == 0)? defaultLen:lenA+1;
	numB = (lenB == 0)? defaultLen:lenB+1;
	numC = (numA > numB)? numA:numB;
	countStr = new char** [numA];
	lcsCount = new int * [numA];
	for (int i=0; i<numA; i++)
	{
		lcsCount[i] = new int  [numB];
		countStr[i] = new char * [numB];
		for (int j=0; j<numB; j++)
			countStr[i][j] = new char [numC];
	}
	for (int i=0; i<numA; i++)
	{
		for (int j=0; j<numB; j++)
		{
			countStr[i][j][0] = '\0';
			lcsCount[i][j] = 0;
		}
	}
}

StrNumCount::StrNumCount()
{
	lenA = 0;
	lenB = 0;
	setCountStr();
	strA = new char [1];
	strB = new char [1];
	strA[0] = '\0';
	strB[0] = '\0';
}

StrNumCount::StrNumCount(const char * A, const char * B)
{
	lenA = std::strlen(A);
	lenB = std::strlen(B);
	setCountStr();
	strA = new char [numA];
	strB = new char [numB];
	std::strcpy(strA,A);
	std::strcpy(strB,B);
}

StrNumCount::~StrNumCount()
{
	delete [] strA;
	delete [] strB;
	for (int i=0; i<numA; i++)
	{
		delete [] lcsCount[i];
		for (int j = 0; j<numB; j++)
		{
			delete [] countStr[i][j];
		}
		delete [] countStr[i];
	}
	delete [] countStr;
	delete [] lcsCount;
}

void StrNumCount::calLCS()
{
	int len;
	for (int i=0; i<lenA; i++)
	{
		for (int j=0; j<lenB; j++)
		{
			if (toupper(strA[i]) == toupper(strB[j]))
			{
				strcpy(countStr[i+1][j+1],countStr[i][j]);
				len = strlen(countStr[i][j]);
				countStr[i+1][j+1][len] = strA[i];
				countStr[i+1][j+1][len+1] = '\0';
				lcsCount[i+1][j+1] = lcsCount[i][j] + 1;
			}
			else
			{
				if (lcsCount[i][j+1] > lcsCount[i+1][j])
				{
					lcsCount[i+1][j+1] = lcsCount[i][j+1];
					strcpy(countStr[i+1][j+1],countStr[i][j+1]);
				}
				else
				{
					lcsCount[i+1][j+1] = lcsCount[i+1][j];
					strcpy(countStr[i+1][j+1],countStr[i+1][j]);
				}
			}
		}
	}
}

void StrNumCount::showSingle(int lena,int lenb)
{
	std::cout << "LCS: " << lcsCount[lena][lenb] << std::endl;
	std::cout << "One of string: " << countStr[lena][lenb] << std::endl;
}

void StrNumCount::showLCSdetail()
{
	for (int i=0; i<numA; i++)
		for (int j=0; j<numB; j++)
		{
			std::cout << "[" << i << ", " << j << "]" <<std::endl;
			showSingle(i,j);
		}
}
