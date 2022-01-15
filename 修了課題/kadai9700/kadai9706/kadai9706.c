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
    printf("‹àŠz=");scanf("%d",&kingaku);
    printf("‹æ•ª=");scanf("%d",&kubun);
    
    tax(kingaku,kubun);


  
  return 0;
}
int tax(int kin, int ku)
{
    

    if(ku == 0)
    {
       return printf("‹àŠz=%.0f\n", kin * 1.08);
    }
    else if(ku == 1)
    {
        return printf("‹àŠz=%d\n", kin);
    }
    else
    {
       return printf("ERROR\n");
    }

}