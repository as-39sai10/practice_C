/*
kadai9707.c
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int mondai(int);
int check(int);


int check(int n)
{
	int kotae;
	int cnt;
	do
	{
		printf("³‰ğ‚Í");scanf("%d",&kotae);
	}while(kotae < 0 || kotae > 4);

	
	if(n == kotae)
	{
		puts("³‰ğ");
        return 1;
	}
    else
	{
		puts("•s³‰ğ");
        return 0;	
	}
    
    
}

int mondai(int n)
{
	int ans = -1;
    
	puts("");
	switch(n)
	{
	case 1:
		puts("–â‘è‚PF“È–ØŒ§‚ÌŒ§’¡Šİ’n‚ÍH");
		puts("‚PF‰F“s‹{s");
		puts("‚QF¬Rs");
		puts("‚RF“úŒõs");
		ans = 1;
		break;
	case 2:
		puts("–â‘è‚QF’†‘T›ŒÎ‚ÍA•W‚‰½‚‚©‚ÈH");
		puts("‚PF‚P‚O‚P‚Q‚");
		puts("‚QF‚P‚Q‚U‚X‚");
		puts("‚RF‚P‚T‚R‚Q‚");
		ans = 2;
		break;
	case 3:
		puts("–â‘è‚RFCNN‚ª‘I‚ñ‚¾u2014”NE¢ŠE‚Ì–²‚Ì—·sæ‚X‘Iv‚ÌêŠ‚Æ‚ÍH");
		puts("‚PF“úŒõ“ŒÆ‹{");
		puts("‚QF‰F“s‹{éLqŠÙ");
		puts("‚RF‚ ‚µ‚©‚ªƒtƒ‰ƒ[ƒp[ƒN");
		ans = 3;
		break;
	case 4:
		puts("–â‘è‚SF“È–ØŒ§Å‘å‚ÌŒö‰€‚ÅA‚©‚½‚­‚è‚Ì‰Ô‚Å—L–¼‚Æ‚¢‚¦‚ÎH");
		puts("‚PF‚İ‚©‚àRŒö‰€");
		puts("‚QFéš¬Œö‰€");
		puts("‚RFƒ‰ƒ‰ƒ““¡‰ª");
		ans = 1;
		break;
	case 5:
		puts("–â‘è‚TF–ˆ“ú‚Ì‚æ‚¤‚É”EÒ‚ªo–v‚·‚é‚Æ‚±‚ë‚Æ‚¢‚¦‚ÎH");
		puts("‚PFíêƒ–Œ´");
		puts("‚QF“úŒõ]ŒË‘º");
		puts("‚RF‚í‚½‚ç‚¹Œk’J");
		ans = 2;
		break;
	default: // NOT REACHE
		break;
	}

	return check(ans);
}

int main(void)
{
	
	int i ;
	int touritu ;
    int cnt = 0;
	

	for(i = 1; i < 6; i++)
	{
	   touritu = mondai(i); printf("\n%d\n",touritu);
       if(touritu == 1)
       {
           cnt++;
       }
       
    }
    
	printf("³‰ğ—¦‚Í%.1f“\n",(cnt / 5.0) * 100);
	return 0;
}