/*
  kadai9705.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
    int tanka;
    int kosuu;

    printf("�P����0����͂���ƁA���͏������I�����܂��B\n");
    printf("�P������͂��Ă������� ==>");scanf("%d",&tanka);

    if(tanka <= 0)
    {
        //end
    }
    else
    {
        printf("���ʂ���͂��Ă������� ==>");scanf("%d",&kosuu);
        printf("%5d�~",tanka);printf("%5d��\n",kosuu);
        printf("%5d�~",tanka * kosuu);printf("%5.0f�~\n",(tanka * kosuu * 1.08));

    }


    return 0;
}
