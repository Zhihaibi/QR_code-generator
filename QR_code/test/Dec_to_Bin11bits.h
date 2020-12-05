#pragma once
#include<math.h>

int* Dec_to_Bin_11(int DEC)//十进制转二进制
{
	int *A;
	A = new int[11];
	for (int j = 0; j < 11; j++)
		A[j] = 0;
	int i = 10;
	while (DEC >= 1)
	{
		A[i] = DEC % 2;
		if (DEC % 2 == 0)
			DEC = DEC / 2;
		else
			DEC = (DEC - 1) / 2;
		i--;
	}
	return A;
}