#pragma once
#include<math.h>

int* Dec_to_Bin_8(int DEC)//十进制转二进制
{
	int *GG;
	GG = new int[8];
	for (int j = 0; j < 8; j++)
		GG[j] = 0;
	int i = 7;
	while (DEC >= 1)
	{
		GG[i] = DEC % 2;
		if (DEC % 2 == 0)
			DEC = DEC / 2;
		else
			DEC = (DEC - 1) / 2;
		i--;
	}
	return GG;
}
