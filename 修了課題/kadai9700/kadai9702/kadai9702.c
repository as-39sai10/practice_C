/*
  kadai9702.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int main( void )
{
    int suuzi;
    int waru;

  printf("割られる数"); scanf("%d", &suuzi);
  printf("割られる数"); scanf("%d", &waru);

  printf("%dを%dで割った余%d\n",suuzi,waru,suuzi % waru );

  
  return 0;
}
