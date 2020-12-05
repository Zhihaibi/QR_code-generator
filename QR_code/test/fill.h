#include <iostream>
#include<math.h>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////
//功能区创建
void Function_create(int(*E)[21], int side)
{
	for (int i = 0; i < side; i++)
		for (int j = 0; j < side; j++)
			E[i][j] = 0;
	for (int i = 0; i <= 20; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			if (i == 0 || i == 6)
				if (j == 0 || j == 1 || j == 2 || j == 3 || j == 4 || j == 5 || j == 6 || j == 14 || j == 15 || j == 16 || j == 17 || j == 18 || j == 19 || j == 20)
					E[i][j] = 1;
			if (i == 1 || i == 5)
				if (j == 0 || j == 6 || j == 14 || j == 20)
					E[i][j] = 1;
			if (i == 2 || i == 3 || i == 4)
				if (j == 0 || j == 2 || j == 3 || j == 4 || j == 6 || j == 14 || j == 16 || j == 17 || j == 18 || j == 20)
					E[i][j] = 1;
			if (i == 14 || i == 20)
				if (j == 0 || j == 1 || j == 2 || j == 3 || j == 4 || j == 5 || j == 6)
					E[i][j] = 1;
			if (i == 15 || i == 19)
				if (j == 0 || j == 6)
					E[i][j] = 1;
			if (i == 16 || i == 17 || i == 18)
				if (j == 0 || j == 2 || j == 3 || j == 4 || j == 6)
					E[i][j] = 1;
			if (i == 6)
				if (j == 8 || j == 10 || j == 12)
					E[i][j] = 1;
			if (j == 6)
				if (i == 8 || i == 10 || i == 12)
					E[i][j] = 1;                                          //基本框架↑
			if (i == 8)                                                   //格式信息↓
				if (j != 9 && j != 10 && j != 11 && j != 12)
					E[i][j] = 1;
			if (j == 8)
				if (i != 9 && i != 10 && i != 11 && i != 12)
					E[i][j] = 1;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//数据区填充
void Upfill(int(*E)[21], int P[], int x, int y, int f, int *R)
{
	for (int i = x; i > (f - 1); i--)
		for (int j = y; j > (y - 2); j--)
		{
			E[i][j] = P[(*R)];
			(*R)++;
		}
}
void Downfill(int(*E)[21], int P[], int x, int y, int f, int *R)
{
	for (int i = x; i < (f + 1); i++)
		for (int j = y; j >(y - 2); j--)
		{
			E[i][j] = P[(*R)];
			(*R)++;
		}
}

void Bffill(int(*E)[21], int P[], int x, int y, int top, int *R)
{
	Upfill(E, P, x, y, top, R);
	Downfill(E, P, top, y - 2, x, R);
}

void Jumpfill(int(*E)[21], int P[], int x, int y, int top, int *R)
{
	Upfill(E, P, x, y, 7, R);
	Bffill(E, P, 5, y, 0, R);
	Downfill(E, P, 7, y - 2, x, R);
}
