/*
  kadai9706.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int tax(int, int);

int main( void )
{
    int kingaku;
    int kubun;
    printf("���z=");scanf("%d",&kingaku);
    printf("�敪=");scanf("%d",&kubun);
    
    tax(kingaku,kubun);


  
  return 0;
}
int tax(int kin, int ku)
{
    

    if(ku == 0)
    {
       return printf("���z=%.0f\n", kin * 1.08);
    }
    else if(ku == 1)
    {
        return printf("���z=%d\n", kin);
    }
    else
    {
       return printf("ERROR\n");
    }

}