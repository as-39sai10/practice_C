/*
  kadai9703.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
	int kisetu;

	printf("”Žš‚ð‘I‘ð‚µ‚Ä‚­‚¾‚³‚¢B\n");
	printf("1.t 2.‰Ä 3.H 4.“~ ‘I‘ð=");scanf("%d",&kisetu);
	
     if(kisetu > 4 || kisetu < 0)
		{
			printf("‘I‘ðŽˆ‚É‚È‚¢”Žš‚Å‚·B\n");
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
