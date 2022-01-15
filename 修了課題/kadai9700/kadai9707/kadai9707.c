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
		printf("正解は");scanf("%d",&kotae);
	}while(kotae < 0 || kotae > 4);

	
	if(n == kotae)
	{
		puts("正解");
        return 1;
	}
    else
	{
		puts("不正解");
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
		puts("問題１：栃木県の県庁所在地は？");
		puts("１：宇都宮市");
		puts("２：小山市");
		puts("３：日光市");
		ans = 1;
		break;
	case 2:
		puts("問題２：中禅寺湖は、標高何ｍかな？");
		puts("１：１０１２ｍ");
		puts("２：１２６９ｍ");
		puts("３：１５３２ｍ");
		ans = 2;
		break;
	case 3:
		puts("問題３：CNNが選んだ「2014年・世界の夢の旅行先９選」の場所とは？");
		puts("１：日光東照宮");
		puts("２：宇都宮餃子館");
		puts("３：あしかがフラワーパーク");
		ans = 3;
		break;
	case 4:
		puts("問題４：栃木県最大の公園で、かたくりの花で有名といえば？");
		puts("１：みかも山公園");
		puts("２：城址公園");
		puts("３：ララン藤岡");
		ans = 1;
		break;
	case 5:
		puts("問題５：毎日のように忍者が出没するところといえば？");
		puts("１：戦場ヶ原");
		puts("２：日光江戸村");
		puts("３：わたらせ渓谷");
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
    
	printf("正解率は%.1f％\n",(cnt / 5.0) * 100);
	return 0;
}