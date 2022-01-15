/*
  kadai9709.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
  int x[5] = {14, 28, 33, 25, 0};
  int i = 0;
  int sum = 0;

  for(i = 0; i < 4;i++)
  {
      //x[4] += x[i];
      sum += x[i];
      printf("x[%d]=%d\n", i, x[i]);
      
  }
puts("\n");
  printf("x[4]=%d\n", sum);


  return 0;
}
