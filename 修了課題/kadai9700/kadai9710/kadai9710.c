/*
  kadai9710.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
    int x[2][5] =
    {
        {14, 28, 33, 25, 0},
        {21, 54, 18, 27, 0},
    };
    int i = 0;

    for(i = 0; i < 4;i++)
  {
      x[0][4] += x[0][i];
      x[1][4] += x[1][i];
      printf("%3d\n",x[0][i]);
      printf("%3d\n",x[1][i]);
  }

  printf(":%d\n", x[0][4]);
  printf(":%d\n", x[1][4]);


    return 0;
}
