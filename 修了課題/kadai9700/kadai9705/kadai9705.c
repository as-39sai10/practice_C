/*
  kadai9705.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
int main( void )
{
    int tanka;
    int kosuu;

    printf("’P‰¿‚É0‚ð“ü—Í‚·‚é‚ÆA“ü—Íˆ—‚ðI—¹‚µ‚Ü‚·B\n");
    printf("’P‰¿‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢ ==>");scanf("%d",&tanka);

    if(tanka <= 0)
    {
        //end
    }
    else
    {
        printf("”—Ê‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢ ==>");scanf("%d",&kosuu);
        printf("%5d‰~",tanka);printf("%5dŒÂ\n",kosuu);
        printf("%5d‰~",tanka * kosuu);printf("%5.0f‰~\n",(tanka * kosuu * 1.08));

    }


    return 0;
}
