/*
  kadai9705.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
    int tanka;
    int kosuu;

    printf("単価に0を入力すると、入力処理を終了します。\n");
    printf("単価を入力してください ==>");scanf("%d",&tanka);

    if(tanka <= 0)
    {
        //end
    }
    else
    {
        printf("数量を入力してください ==>");scanf("%d",&kosuu);
        printf("%5d円",tanka);printf("%5d個\n",kosuu);
        printf("%5d円",tanka * kosuu);printf("%5.0f円\n",(tanka * kosuu * 1.08));

    }


    return 0;
}
