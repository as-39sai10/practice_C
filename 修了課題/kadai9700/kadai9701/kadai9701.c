/*
  kadai9701.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int main(void)
{
  int kingaku; // ã‡äz
  int zei; // ê≈ã‡
  int zeikomi = 0; // ê≈çûã‡äz

  printf("ã‡äz="); scanf("%d", &kingaku);
  zei = kingaku * 0.08;
  zeikomi = kingaku + zei;
  printf("ê≈çûã‡äz=%d\n", zeikomi);
  return 0;
}
