/*
  kadai9708.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
    int x[] = {15, 25, 5, 45, 58, 77, 21, 68, 18, 35};
    int y[] = { 6, 7, 2, 5, 3, 4, 8, 1, 9, 10};
    int z[10] =  {0};
    int sum;

    int hyouzi = 0;

    while(hyouzi != -1)
    {
        printf("ï\é¶Ç∑ÇÈêîÇÕÅH");scanf("%d",&hyouzi);

        if(hyouzi == -1)
        {
            puts("Ç≤Ç≠ÇÎÇ§Ç≥Ç‹Ç≈ÇµÇΩ");
        }
        else
        {
            printf("x[%d]=%d\n", hyouzi, x[hyouzi - 1]);
            printf("y[%d]=%d\n", hyouzi, y[hyouzi - 1]);

            printf("z[%d]=%d\n", hyouzi, x[hyouzi - 1] * y[hyouzi - 1]);
        }


    }
    return 0;
}

