/*
  kadai9702.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int main( void )
{
    int suuzi;
    int waru;

  printf("�����鐔"); scanf("%d", &suuzi);
  printf("�����鐔"); scanf("%d", &waru);

  printf("%d��%d�Ŋ������]%d\n",suuzi,waru,suuzi % waru );

  
  return 0;
}
