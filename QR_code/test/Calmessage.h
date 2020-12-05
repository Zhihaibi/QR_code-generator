#pragma once
#include<iostream>
using namespace std;
#include <string>
#include<math.h>

int Bin_to_Dec(int A[8])
{
	int sum = 0;
	sum = A[0] * pow(2.0, 7) + A[1] * pow(2.0, 6) + A[2] * pow(2.0, 5) + A[3] * pow(2.0, 4) + A[4] * pow(2.0, 3) + A[5] * pow(2.0, 2) + A[6] * pow(2.0, 1) + A[7];
	return sum;
}

int* Dec_to_Bin(int DEC)//十进制转二进制
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

int PaddingBytes1[8] = { 1,1,1,0,1,1,0,0 };
int PaddingBytes2[8] = { 0,0,0,1,0,0,0,1 };

bool Judge(char n[100])
{
	for (unsigned i = 0; i < strlen(n); i++)
	{
		int tmp = (int)n[i];
		if (tmp >= 48 && tmp <= 57)
			continue;
		else
			return false;
	}
	return true;
}

int * Binary(int a, int n)
{
	int *b = new int[n];
	for (int i = 0; i < n; i++)
		b[i] = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		b[i] = a % 2;
		a = a / 2;
		if (a == 0)
			break;
	}
	return b;
}

int* NUM_init(char n[100])                            //数字类型的初始化
{
	int LENa = strlen(n);
	int a[100], b[100], j = LENa - 1;
	for (int j = 0; j < LENa; j++)
		a[j] = n[j] - '0';                //字符串转数字a


	if (LENa % 3 == 0)                     //转成三位数字的数组b
	{
		for (int i = 0; i < LENa; i++)
			if (i % 3 == 0)
				b[i / 3] = a[i] * 100 + a[i + 1] * 10 + a[i + 2];
	}

	if (LENa % 3 == 1)
	{
		for (int i = 0; i < LENa - 1; i++)
			if (i % 3 == 0)
				b[i / 3] = a[i] * 100 + a[i + 1] * 10 + a[i + 2];
		b[(LENa - 1) / 3] = a[LENa - 1];
	}
	if (LENa % 3 == 2)
	{
		for (int i = 0; i < LENa - 2; i++)
			if (i % 3 == 0)
				b[i / 3] = a[i] * 100 + a[i + 1] * 10 + a[i + 2];
		b[(LENa - 2) / 3] = a[LENa - 2] * 10 + a[LENa - 1];
	}
	int LENb = (LENa + 2) / 3;


	int *c;
	c = new int[128];
	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
	c[3] = 1;

	int *p = Binary(LENa, 10);
	for (int i = 4; i < 14; i++)
		c[i] = p[i - 4];
	if (LENa % 3 == 0)
	{
		for (int i = 0; i < LENb; i++)
		{
			p = Binary(b[i], 10);
			for (int j = 14 + 10 * i; j < 24 + 10 * i; j++)
				c[j] = p[j - 14 - 10 * i];
		}
		if (14 + 10 * LENb < 128)
		{
			if (14 + 10 * LENb > 125)
				for (int i = 14 + 10 * LENb; i < 128; i++)
					c[i] = 0;
			else
			{
				for (int i = 14 + 10 * LENb; i < 18 + 10 * LENb; i++)
					c[i] = 0;
				int EndN = (18 + 10 * LENb) % 8;
				if (EndN == 0)
				{
					int PaddingN = ((128 - (18 + 10 * LENb)) / 8) % 2;
					if (PaddingN == 0)
						for (int i = 18 + 10 * LENb; i < 128; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
					else
					{
						for (int i = 18 + 10 * LENb; i < 120; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
						for (int i = 120; i < 128; i++)
							c[i] = PaddingBytes1[i - 120];
					}
				}
				else
				{
					for (int i = 18 + 10 * LENb; i < 26 + 10 * LENb - EndN; i++)
						c[i] = 0;
					int PaddingN = ((128 - (26 + 10 * LENb - EndN)) / 8) % 2;
					if (PaddingN == 0)
						for (int i = 26 + 10 * LENb - EndN; i < 128; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
					else
					{
						for (int i = 26 + 10 * LENb - EndN; i < 120; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
						for (int i = 120; i < 128; i++)
							c[i] = PaddingBytes1[i - 120];
					}
				}
			}
		}
	}
	if (LENa % 3 == 1)
	{
		for (int i = 0; i < LENb - 1; i++)
		{
			p = Binary(b[i], 10);
			for (int j = 14 + 10 * i; j < 24 + 10 * i; j++)
				c[j] = p[j - 14 - 10 * i];
		}
		p = Binary(b[LENb - 1], 4);
		for (int i = 4 + LENb * 10; i < 8 + LENb * 10; i++)
			c[i] = p[i - 4 - LENb * 10];
		if (8 + LENb * 10 < 128)
		{
			if (8 + LENb * 10 > 125)
				for (int i = 8 + LENb * 10; i < 128; i++)
					c[i] = 0;
			else
			{
				for (int i = 8 + LENb * 10; i < 12 + LENb * 10; i++)
					c[i] = 0;
				int EndN = (12 + LENb * 10) % 8;
				if (EndN == 0)
				{
					int PaddingN = (128 - (12 + LENb * 10) / 8) % 2;
					if (PaddingN == 0)
					{
						for (int i = 12 + LENb * 10; i < 128; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
					}
					else
					{
						for (int i = 12 + LENb * 10; i < 120; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
						for (int i = 120; i < 128; i++)
							c[i] = PaddingBytes1[i - 120];
					}
				}
				else
				{
					for (int i = 12 + LENb * 10; i < 20 + LENb * 10 - EndN; i++)
						c[i] = 0;
					int PaddingN = ((128 - (20 + LENb * 10 - EndN)) / 8) % 2;
					if (PaddingN == 0)
					{
						for (int i = 20 + LENb * 10 - EndN; i < 128; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
					}
					else
					{
						for (int i = 20 + LENb * 10 - EndN; i < 120; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
						for (int i = 120; i < 128; i++)
							c[i] = PaddingBytes1[i - 120];
					}
				}
			}
		}
	}
	if (LENa % 3 == 2)
	{
		for (int i = 0; i < LENb - 1; i++)
		{
			p = Binary(b[i], 10);
			for (int j = 14 + 10 * i; j < 24 + 10 * i; j++)
				c[j] = p[j - 14 - 10 * i];
		}
		p = Binary(b[LENb - 1], 7);
		for (int i = 4 + LENb * 10; i < 11 + LENb * 10; i++)
			c[i] = p[i - 4 - LENb * 10];
		if (11 + LENb * 10 < 128)
		{
			if (11 + LENb * 10 > 125)
				for (int i = 11 + LENb * 10; i < 128; i++)
					c[i] = 0;
			else
			{
				for (int i = 11 + LENb * 10; i < 15 + LENb * 10; i++)
					c[i] = 0;
				int EndN = (15 + LENb * 10) % 8;
				if (EndN == 0)
				{
					int PaddingN = (128 - (15 + LENb * 10) / 8) % 2;
					if (PaddingN == 0)
					{
						for (int i = 15 + LENb * 10; i < 128; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
					}
					else
					{
						for (int i = 15 + LENb * 10; i < 120; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
						for (int i = 120; i < 128; i++)
							c[i] = PaddingBytes1[i - 120];
					}
				}
				else
				{
					for (int i = 15 + LENb * 10; i < 23 + LENb * 10 - EndN; i++)
						c[i] = 0;
					int PaddingN = ((128 - (23 + LENb * 10 - EndN)) / 8) % 2;
					if (PaddingN == 0)
					{
						for (int i = 23 + LENb * 10 - EndN; i < 128; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
					}
					else
					{
						for (int i = 23 + LENb * 10 - EndN; i < 120; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
						for (int i = 120; i < 128; i++)
							c[i] = PaddingBytes1[i - 120];
					}
				}
			}
		}
	}
	//for (int i = 0; i <= LENb - 1; i++)
	//	cout << b[i] << endl;
	//for (int i = 0; i < 128; i++)
	//	cout << c[i];
	return c;
}

int* ALPHA_init(char n[100])                  //大写字母与数字组合
{
	int LENa = strlen(n);
	int a[100], b[100];
	for (int i = 0; i < LENa; i++)
	{
		if (n[i] >= 48 && n[i] <= 57)
			a[i] = n[i] - '0';
		if (n[i] >= 65 && n[i] <= 90)
			a[i] = n[i] - '0' - 7;
		if (n[i] == ' ')
			a[i] = n[i] - '0' + 52;
		if (n[i] == '$' || n[i] == '%')
			a[i] = n[i] - '0' + 49;
		if (n[i] == '*' || n[i] == '+')
			a[i] = n[i] - '0' + 45;
		if (n[i] == '-' || n[i] == '.' || n[i] == '/')
			a[i] = n[i] - '0' + 44;
		if (n[i] == ':')
			a[i] = n[i] - '0' + 34;
	}                                        //a[len-1]
	if (LENa % 2 == 0)                       //转成两位数字的数组b[(LENa-1)/2]
		for (int i = 0; i < LENa; i++)
			if (i % 2 == 0)
				b[i / 2] = a[i] * 45 + a[i + 1];
	if (LENa % 2 == 1)                       //
	{
		for (int i = 0; i < LENa - 1; i++)
			if (i % 2 == 0)
				b[i / 2] = a[i] * 45 + a[i + 1];
		b[(LENa - 1) / 2] = a[LENa - 1];
	}
	int LENb = (LENa + 1) / 2;

	int *c;
	c = new int[128];
	c[0] = 0;
	c[1] = 0;
	c[2] = 1;
	c[3] = 0;

	int *p = Binary(LENa, 9);
	for (int i = 4; i < 13; i++)
		c[i] = p[i - 4];
	if (LENa % 2 == 0)//偶数
	{
		for (int i = 0; i < LENb; i++)
		{
			p = Binary(b[i], 11);
			for (int j = 13 + 11 * i; j < 24 + 11 * i; j++)
				c[j] = p[j - 13 - 11 * i];
		}
		if ((LENb - 1) * 11 + 24 < 128)
		{
			if ((LENb - 1) * 11 + 24 > 125)//结束符
				for (int i = (LENb - 1) * 11 + 24; i < 128; i++)
					c[i] = 0;
			else
			{
				for (int i = (LENb - 1) * 11 + 24; i < (LENb - 1) * 11 + 28; i++)
					c[i] = 0;
				int EndN = ((LENb - 1) * 11 + 28) % 8;
				if (EndN == 0)
				{
					int PaddingN = ((128 - (LENb - 1) * 11 - 28) / 8) % 2;
					if (PaddingN == 0)
						for (int i = (LENb - 1) * 11 + 28; i < 128; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
					else
					{
						for (int i = (LENb - 1) * 11 + 28; i < 120; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
						for (int j = 0; j < 8; j++)
							c[120 + j] = PaddingBytes1[j];
					}
				}
				else
				{
					for (int i = (LENb - 1) * 11 + 28; i < (LENb - 1) * 11 + 36 - EndN; i++)
						c[i] = 0;
					int PaddingN = ((128 - (LENb - 1) * 11 - 36 + EndN) / 8) % 2;
					if (PaddingN == 0)
						for (int i = (LENb - 1) * 11 + 36 - EndN; i < 128; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
					else
					{
						for (int i = (LENb - 1) * 11 + 36 - EndN; i < 120; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
						for (int j = 0; j < 8; j++)
							c[120 + j] = PaddingBytes1[j];
					}
				}
			}
		}
	}
	if (LENa % 2 == 1)//奇数
	{
		for (int i = 0; i < LENb - 1; i++)//编码
		{
			p = Binary(b[i], 11);
			for (int j = 13 + 11 * i; j < 24 + 11 * i; j++)
				c[j] = p[j - 13 - 11 * i];
		}
		p = Binary(b[LENb - 1], 6);
		for (int i = (LENb - 1) * 11 + 13; i < (LENb - 1) * 11 + 19; i++)
			c[i] = p[i - (LENb - 1) * 11 - 13];
		if ((LENb - 1) * 11 + 19 < 128)
		{
			if ((LENb - 1) * 11 + 19 > 125)//结束符
				for (int i = (LENb - 1) * 11 + 19; i < 128; i++)
					c[i] = 0;
			else
			{
				for (int i = (LENb - 1) * 11 + 19; i < (LENb - 1) * 11 + 23; i++)
					c[i] = 0;
				int EndN = ((LENb - 1) * 11 + 23) % 8;
				if (EndN == 0)
				{
					int PaddingN = ((128 - (LENb - 1) * 11 - 23) / 8) % 2;
					if (PaddingN == 0)
						for (int i = (LENb - 1) * 11 + 23; i < 128; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
					else
					{
						for (int i = (LENb - 1) * 11 + 23; i < 120; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
						for (int j = 0; j < 8; j++)
							c[120 + j] = PaddingBytes1[j];
					}
				}
				else
				{
					for (int i = (LENb - 1) * 11 + 23; i < (LENb - 1) * 11 + 31 - EndN; i++)
						c[i] = 0;
					int PaddingN = ((128 - (LENb - 1) * 11 - 31 + EndN) / 8) % 2;
					if (PaddingN == 0)
						for (int i = (LENb - 1) * 11 + 31 - EndN; i < 128; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
					else
					{
						for (int i = (LENb - 1) * 11 + 31 - EndN; i < 120; i += 16)
							for (int j = 0; j < 8; j++)
							{
								c[i + j] = PaddingBytes1[j];
								c[i + j + 8] = PaddingBytes2[j];
							}
						for (int j = 0; j < 8; j++)
							c[120 + j] = PaddingBytes1[j];
					}
				}
			}
		}
	}
	//for (int i = 0; i <= LENb - 1; i++)
	//	cout << b[i] << endl;
	//for (int i = 0; i < 128; i++)
	//	cout << c[i];
	return c;
}


int* init()
{
	int *mesback;
	//	mesback = new int[128];
	char n[100];
	cin.getline(n, 100);
	if (Judge(n) == true)
		mesback = NUM_init(n);
	else
		mesback = ALPHA_init(n);
	return mesback;
	//得到一串一位数组c[128]
}