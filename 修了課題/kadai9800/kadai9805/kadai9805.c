/*
kadai9805.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main( void )
{
    char suuti[256] ;
    int  atai = 0;

    int check;
    int cnt;
    int min;
    int max;
    int error = 0;

    cnt = 0;
    min = 10000; // 最小値を見つけるための初期値(4文字以内なので、10000未満の数値となる)
    max = -1; // 最大値を見つけるための初期値(仕様では0以上の数が入力される)

    while(1)
    {
        printf("数値=");scanf("%s", suuti);
        if(suuti[0] == '@')break;

        atai    = 0; // 入力された数値
        error   = 0; // 入力エラーの発生
        check   = 0;

        while(suuti[check] != '\0')
        {
            if(check >= 4)
            {
                printf("4桁以内の数字を入力してください。\n");
                error = 1;
                break;
            }
            if(!isdigit(suuti[check]))
            {
                printf("数字を入力してください。\n");
                error = 1;
                break;
            }

            atai *= 10; // val = val * 10; --> 桁上がりさせる 12 --> 120
            atai += suuti[check++] - '0'; // 1の位に数を加算する。その後、位置(pos)を1つ後方に移動する

        }
        if(error == 0)
        {
            cnt++; // データ数をカウント
            if(atai < min) min = atai;
            if(atai > max) max = atai;
        }
    }


    printf("データ数=%d 最小値=%d 最大値=%d\n", cnt, min, max);

}
