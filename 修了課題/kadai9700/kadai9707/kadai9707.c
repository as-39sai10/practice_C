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
		printf("������");scanf("%d",&kotae);
	}while(kotae < 0 || kotae > 4);

	
	if(n == kotae)
	{
		puts("����");
        return 1;
	}
    else
	{
		puts("�s����");
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
		puts("���P�F�Ȗ،��̌������ݒn�́H");
		puts("�P�F�F�s�{�s");
		puts("�Q�F���R�s");
		puts("�R�F�����s");
		ans = 1;
		break;
	case 2:
		puts("���Q�F���T���΂́A�W���������ȁH");
		puts("�P�F�P�O�P�Q��");
		puts("�Q�F�P�Q�U�X��");
		puts("�R�F�P�T�R�Q��");
		ans = 2;
		break;
	case 3:
		puts("���R�FCNN���I�񂾁u2014�N�E���E�̖��̗��s��X�I�v�̏ꏊ�Ƃ́H");
		puts("�P�F�������Ƌ{");
		puts("�Q�F�F�s�{�L�q��");
		puts("�R�F���������t�����[�p�[�N");
		ans = 3;
		break;
	case 4:
		puts("���S�F�Ȗ،��ő�̌����ŁA��������̉ԂŗL���Ƃ����΁H");
		puts("�P�F�݂����R����");
		puts("�Q�F�隬����");
		puts("�R�F����������");
		ans = 1;
		break;
	case 5:
		puts("���T�F�����̂悤�ɔE�҂��o�v����Ƃ���Ƃ����΁H");
		puts("�P�F��ꃖ��");
		puts("�Q�F�����]�ˑ�");
		puts("�R�F�킽�点�k�J");
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
    
	printf("���𗦂�%.1f��\n",(cnt / 5.0) * 100);
	return 0;
}