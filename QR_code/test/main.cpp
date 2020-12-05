#include<iostream>
using namespace std;
#include"Dec_to_Bin 8bits.h"
#include"Dec_to_Bin11bits.h"
#include"mask.h"
#include"fill.h"
#include"Rs_code.h"
#include"Calmessage.h"

int main()
{
	int *originalmessage;
	originalmessage = init();//信息输入
     ////按8 个 8 个分开,放在一个二维数组中；
    int pp = 0;
	int Finalmes[16][8];
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Finalmes[i][j] = originalmessage[pp];
			pp++;
		}
	}
	
	/////////////转为10进制////////////////////////////
	int AAA[8];
	int mesrs[16];
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
			AAA[j] = Finalmes[i][j];
		mesrs[i] = Bin_to_Dec(AAA);
	}


	
	int ECCcodenum = 10;
	int mesploycoef[16];
	for (int i = 0; i < 16; i++)
	{
		mesploycoef[i] = mesrs[i];
	}
	
	int mesploycoefnu = 16;//数据码的长度////////////////
	
	
	////////////////////算纠错码/////////////////////////////////////////////
	int *RS;
	RS = Cal_Rs_code(mesploycoef, mesploycoefnu);//十进制纠错码
	

	int Binary[10][8] = { 0 };//存放二进制纠错码的二维数组
	int *CC;
	CC = new int[8];
	for (int j = 0; j<10; j++)//纠错码十进制转二进制
	{
		
		
		CC = Dec_to_Bin_8(RS[j]);

	
		for (int i = 0; i<8; i++)
		{
			Binary[j][i] = CC[i];

		}
		
	}
	

	int test[16][8] = {0};
	for(int i=0;i<16;i++)
	{
	for(int j =0;j<8;j++)
	{
		test[i][j] = Finalmes[i][j];
		
	}
	
	}



	////////////////数据码与纠错码的结合//////////////////////////////////////////////
	int test2[26][8] = { 0 };
	for (int i = 0; i<16; i++)
	{
		for (int j = 0; j<8; j++)
		{
			test2[i][j] = test[i][j];
		}

	}

	for (int i = 16; i<26; i++)
	{
		for (int j = 0; j<8; j++)
		{
			test2[i][j] = Binary[i - 16][j];
		}

	}


/////////////////////////////////////////////////////////////////////////////////填充


	int version = 1;
	int side = (version - 1) * 4 + 21;
	int mask[200][200], E[21][21], num;
	int P[1000], R = 0, pc = 0;
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 8; j++)
		{
			P[pc] = test2[i][j];
			pc++;
		}
	Function_create(E, side);
	Bffill(E, P, side - 1, side - 1, 9, &R);
	Bffill(E, P, side - 1, side - 5, 9, &R);
	Jumpfill(E, P, side - 1, side - 9, 0, &R);
	Upfill(E, P, side - 9, 8, 9, &R);
	Downfill(E, P, 9, 5, side - 9, &R);
	Bffill(E, P, side - 9, 3, 9, &R);
	//填充部分
	///////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	//掩码部分
	num =5;
	Format_information_fill(E, num, side);
	Print(mask, E, num, side);
	///////////////////////////////////////////////////////////////////////////////////////

	system("pause");
	return 0;
}