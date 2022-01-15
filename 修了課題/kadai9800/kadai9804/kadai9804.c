/*
  kadai9804.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
    int sales[7]={7, 6, 5, 4, 5, 9, 10};

    int i = 0;
    int j = 0;
    int k = 0;
    double hosi[7] =  {0};
    int youbi[7] ={0};


    for(i = 10; i >= 1; i--)    
    {
      for(j = 0; j < 7; j++)
      {
        if(sales[j] < i)printf("  "); 
        if(sales[j] >= i)printf(" *");        
      }
        puts("\n");

    }

    puts("----------------\n");
    puts(" m t w s f s s\n");







  return 0;
}
