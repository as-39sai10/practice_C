/*
  kadai9801.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int main( void )
{
  int sales[31] =
  {
    122, 93,135,151,166,272,249,
    187,192, 95,108,144,162,203,
     85,110,133, 68,125,185,231,
    121,133, 75, 81,117,246,281,
    160,124, 77,
  };
  
  int goukei = 0;
  int i =  0;

  for(i = 0; i < 31; i++)
  {
      goukei += sales[i];
      printf("%d‰~\n",goukei);
  }
  puts("");
  printf("”„ã‹àŠz‚ÍA%d‰~‚Å‚·B\n", goukei);

  return 0;
}
