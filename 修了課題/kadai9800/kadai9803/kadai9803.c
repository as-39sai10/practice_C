/*
  kadai9803.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
    int sales[5][7] ={
        { 122,  93, 135, 151, 166, 272, 249},
        { 187, 192,  95, 108, 144, 162, 203},
        {  85, 110, 133,  68, 125, 185, 231},
        { 121, 133,  75,  81, 117, 246, 281},
        { 160, 124,  77,   0,   0,   0,   0}
    };

    int i = 0;
    int j = 0;
    int k = 0;
    double hosi[7] =  {0};
    int youbi[7] ={0};

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 7; j++)
        { 
              youbi[j] += sales[i][j];                
        }
    }

    for(k = 0; k < 7; k++)
    {       
        switch(k)
      {
        case 0 : puts("ŒŽ");break;
        case 1 : puts("‰Î");break;
        case 2 : puts("…");break;
        case 3 : puts("–Ø");break;
        case 4 : puts("‹à");break;
        case 5 : puts("“y");break;
        case 6 : puts("“ú");break;
      }
        hosi[k] = (youbi[k] / 964.0) * 10.0;
            
       for(i = 0; i < hosi[k] - 0.9; i++)
             {
                 printf("* ");
       }
       puts("\n");
    }

  return 0;
}
