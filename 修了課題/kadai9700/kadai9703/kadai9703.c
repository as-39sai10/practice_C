/*
  kadai9703.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
	int kisetu;

	printf("数字を選択してください。\n");
	printf("1.春 2.夏 3.秋 4.冬 選択=");scanf("%d",&kisetu);
	
     if(kisetu > 4 || kisetu < 0)
		{
			printf("選択肢にない数字です。\n");
		}
     else

		switch(kisetu)
		{
		case 1 : puts("SPRING"); break;
		case 2 : puts("SUMMER"); break;
		case 3 : puts("AUTUMN"); break;
		case 4 : puts("WINTER"); break;
		}
		


		return 0;
	}
