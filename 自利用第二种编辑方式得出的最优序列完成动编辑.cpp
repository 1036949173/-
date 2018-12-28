//mystring.h文件

#pragma once

#include <iostream>
using namespace std;
class mystring
{
public:
	mystring();
	~mystring();
	void mcopy(char *x, char *z, int &i, int &j);
	void replace(char * z, int &i, char c, int &j);//z[j]=c
	void idelete(int &i);                       
	void insert(char * z, int &i, char c); //z[j]=c
	void exchange(char *x, char *z, int &i, int &j);
	void stop(int &i, int m);
private:
	//int m_length;
};


//mystring.cpp文件

#include "mystring.h"


mystring::mystring()
{
}

mystring::~mystring()
{
}

void mystring::mcopy(char *x, char *z, int &i, int &j)
{
	z[j] = x[i];
	i++;
	j++;
}

void mystring::replace(char * z, int &i, char c, int &j)
{
	z[i] = c;
	i++;
	j++;
}

void mystring::idelete(int & i)
{
	i++;
}

void mystring::insert(char * z, int &j, char c)
{
	z[j] = c;
	j++;
}

void mystring::exchange(char *x, char *z, int &i, int &j)
{
	z[j] = x[i + 1];
	z[j + 1] = x[i];
	i += 2;
	j += 2;
}


void mystring::stop(int & i, int m)
{
	i=m+1;
}

//自动编辑.cpp

#include <iostream>
#include "mystring.h"
using namespace std;

int i, j;
int  dp[101][101];

//1 1 2 2 2 1 4 1 2 2             样例序列
//4, 2, 1, 1, 2, 2, 1, 2, 1, 1, 4  DNA序列的自动编辑序列
enum { cop = 1, replace, del, insert, twi, kill };
char z[20];
int main() 
{
	char x[] = "GATCGGCAT", y[] = "CAATGTGAATC";
	//char x[] = "algorithm", y[] = "altruistic";

	//int arr[15] = { 1, 1, 2, 2, 2, 1, 4, 1, 2, 2 };
	int arr[15] = { 4 ,2, 1, 1 ,2, 2, 1 ,2 ,1 ,1, 4 };
	
	//int arr[15] = { 2,2,2,2,2,2,2,2,2,4};     //自编序列，简单明了先删除直到x序列结束，然后插入y的最后一个
	int l1 = strlen(x), l2 = strlen(y);
	mystring mu;
	int i = 0, j = 0, k = 0;// i->x,j->z
	while(j<l2)
	{
		if (arr[k] == 1)
		{
			mu.mcopy(x, z, i, j);
		}
		else if (arr[k] == 2)
		{
			mu.replace(z, j, y[j], i);
		}
		else if (arr[k] == 3)
		{
			mu.idelete(i);
		}
		else if (arr[k] == 4)
		{
			mu.insert(z, j, y[j]);
		}
		else if (arr[k] == 5)
		{
			mu.exchange(x, z, i, j);
		}
		k++;
	}
	for (int i = 0; i < l2; i++)
	{
		cout << z[i];
	}
	cout << '\n';
    return 0;
}


