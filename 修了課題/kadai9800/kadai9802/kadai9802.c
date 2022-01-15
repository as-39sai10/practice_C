/*
kadai9802.c
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

    int goukei = 0;
    int i =  0;
    int j =  0;
    int k =  0;
    int youbi[7] ={0};

    
    
    for(j = 0; j < 5; j++)
    {
        for(i = 0; i < 7; i++)
        { 
            youbi[i] += sales[j][i];
            
        }    
      
    }
    
    
    goukei = youbi[0] + youbi[1] + youbi[2] + youbi[3] + youbi[4] + youbi[5] + youbi[6];

    printf("  ŒŽ  ‰Î  …  –Ø  ‹à  “y  “ú   ‡Œv\n");
    printf("%4d%4d%4d%4d%4d%4d%4d%5d\n",
        youbi[0]
       ,youbi[1]
       ,youbi[2]
       ,youbi[3]
       ,youbi[4]
       ,youbi[5]
       ,youbi[6]
       ,goukei);


    return 0;
}
