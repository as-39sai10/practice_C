/*
  kadai9701.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int main(void)
{
  int kingaku; // ���z
  int zei; // �ŋ�
  int zeikomi = 0; // �ō����z

  printf("���z="); scanf("%d", &kingaku);
  zei = kingaku * 0.08;
  zeikomi = kingaku + zei;
  printf("�ō����z=%d\n", zeikomi);
  return 0;
}
