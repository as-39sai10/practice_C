/*
  kadai9704.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
    int suugaku;
    int eigo;

    printf("���w�̓��_=");scanf("%d",&suugaku);
    printf("�p��̓��_=");scanf("%d",&eigo);

    printf("���ϓ_=%.2f\n",(double)(suugaku+eigo) / 2.0 ); 
  return 0;
}
