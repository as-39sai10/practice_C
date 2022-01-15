/*
  kadai9704.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
    int suugaku;
    int eigo;

    printf("数学の得点=");scanf("%d",&suugaku);
    printf("英語の得点=");scanf("%d",&eigo);

    printf("平均点=%.2f\n",(double)(suugaku+eigo) / 2.0 ); 
  return 0;
}
