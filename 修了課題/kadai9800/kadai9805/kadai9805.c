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
    min = 10000; // �ŏ��l�������邽�߂̏����l(4�����ȓ��Ȃ̂ŁA10000�����̐��l�ƂȂ�)
    max = -1; // �ő�l�������邽�߂̏����l(�d�l�ł�0�ȏ�̐������͂����)

    while(1)
    {
        printf("���l=");scanf("%s", suuti);
        if(suuti[0] == '@')break;

        atai    = 0; // ���͂��ꂽ���l
        error   = 0; // ���̓G���[�̔���
        check   = 0;

        while(suuti[check] != '\0')
        {
            if(check >= 4)
            {
                printf("4���ȓ��̐�������͂��Ă��������B\n");
                error = 1;
                break;
            }
            if(!isdigit(suuti[check]))
            {
                printf("��������͂��Ă��������B\n");
                error = 1;
                break;
            }

            atai *= 10; // val = val * 10; --> ���オ�肳���� 12 --> 120
            atai += suuti[check++] - '0'; // 1�̈ʂɐ������Z����B���̌�A�ʒu(pos)��1����Ɉړ�����

        }
        if(error == 0)
        {
            cnt++; // �f�[�^�����J�E���g
            if(atai < min) min = atai;
            if(atai > max) max = atai;
        }
    }


    printf("�f�[�^��=%d �ŏ��l=%d �ő�l=%d\n", cnt, min, max);

}
