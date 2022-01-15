//watchtest02.c
//24���Ԏ��v
//S1�Ŏ�,S2�ŕ�,S3�ŕb��ύX�ł���

#include<machine.h>
#include "iodefine.h"
#include "lcd.h"

#pragma interrupt int_imia0(vect=24)	//���荞�݊֐��̐錾

/***** define *****/

// ITU ch0�Ŏg�p���郌�W�X�^
#define TSTR  (*((volatile unsigned char *)0xFFFF60))    // ITU ch0
#define TCR0  (*((volatile unsigned char *)0xFFFF64))
#define TIER0 (*((volatile unsigned char *)0xFFFF66))
#define TSR0  (*((volatile unsigned char *)0xFFFF67))
#define GRA0  (*((volatile unsigned short *)0xFFFF6A))

#define P4DDR (*(volatile unsigned char *)0xFFFFC5)
#define P4DR  (*(volatile unsigned char *)0xFFFFC7)
#define P4PCR (*(volatile unsigned char *)0xFFFFDA)


/****** gloval ******/
volatile unsigned short h,m,s,count;

/******* timer0 interrupt *******/
void int_imia0(void){
	TSR0 &= ~0x01;	// �����ݔ����t���O���N���A
	count--;		// �񐔃J�E���g�ϐ���-1
	if(count==0){	// �J�E���g��0�ɂȂ�����i1�b�o�߂�����j
		s++;
		if(s > 59){
			s = 0;
			m++;
			if(m > 59){
				m = 0;
				h++;
				if(h > 23){
					h = 0;
				}
			}
		}
		count=50;	// �J�E���g�l�����ɖ߂�
	}
}

/********************************************************
* ���C��
********************************************************/
void main(void){

	unsigned char newstate,oldstate;

    P4DDR=0x00;
    P4PCR=0xFF;
	
	TCR0 |= 0x23;	  // ITU0�̐ݒ�F�����N���b�N1/8���J�E���g���AGRA0�Ƃ̃R���y�A�}�b�`�ŃJ�E���^�N���A
	GRA0 = 39999;	  // �J�E���g�l��GRA0�ɐݒ�
	TIER0 |= 0x01;	  // GRA0�Ƃ̃R���y�A�}�b�`�Ŋ����ݗv��
	
	set_imask_ccr(0); // �����ݎg�p
	
	count = 50;		  // �����݉񐔂��J�E���g����ϐ���50���� �����ݎ�����1/50�i20ms�j
					  // 20ms�~50��1sec�i1�b�𐔂���j
	TSTR |= 0x01;	  // ITU0�X�^�[�g
					  
	LCD_Init();
	
	oldstate = ~P4DR & 0xF0;//SW�̏����擾.���4bit�̂�.���̓}�X�N.
	wait(10);//�`���^�����O�h�~
	while(1){		    
		newstate = ~P4DR & 0xF0;//SW�̏����擾.���4bit�̂�.���̓}�X�N.
		wait(10);//�`���^�����O�h�~
		if(oldstate != newstate){						//SW�̏�Ԃ��ω�
			if(oldstate == 0x00 && newstate == 0x10){   //S1��������
				h++;
				if(h > 23){
					h = 0;
				}
			}
			if(oldstate == 0x00 && newstate == 0x20){	//S2��������
				m++;
				if(m > 59){
					m = 0;
				}
			}
			if(oldstate == 0x00 && newstate == 0x40){	//S3�������Ƃ�
				s++;
				if(s > 59){
					s = 0;
				}
			}
		}
		oldstate = newstate;
		LCD_Locate(0,0);
		LCD_Putchar(h/10+'0');
		LCD_Putchar(h%10+'0');
		LCD_Putchar(':');
		LCD_Putchar(m/10+'0');
		LCD_Putchar(m%10+'0');
		LCD_Putchar(':');
		LCD_Putchar(s/10+'0');
		LCD_Putchar(s%10+'0');
	}
}

