/*
  kadai9806.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
    int bingo[5][5] ={
        {  8,  1, 22, 10,  5},
        { 20, 17,  4, 15, 24},
        { 14,  7, 11, 25, 18},
        {  2, 23, 19,  3, 12},
        { 16,  6,  9, 13, 21}
    };

    int kuzi = 0;
    int agari = 0; //bingo end


    int i = 0;
    int j = 0;
  
    while(1)
    {

        puts("BINGO GAME!!\n");
        printf("êîíl=");scanf("%d", kuzi);

        for(i = 0; i < 5; i++)
        {
            for(j = 0; j < 5; j++)
            {
                if(bingo[i][j] == kuzi && kuzi != 0)
                {
                    bingo[i][j] = 0;
                }
                else
                {
                    break;
                }
            }
        }
    }


  return 0;
}
