//watchtest03.c
//24���Ԏ��v
//DIP-SW��1���I���ɂ��邱�ƂŃZ�b�e�B���O���[�h�Ɉڍs.���v���X�g�b�v����.
//DIP-SW��2���I���ɂ��邱�ƂŃA���[�����[�h�Ɉڍs.
//DIP-SW��3���I���ɂ��邱�ƂŃA���[���I��.�A���[���ݒ莞���ɂȂ��P5��LED1���_��.
//���i�ǉ��j�@ �V�@�@�@�@�@�@�u�U�[�o��[�h]�̉���LED�_�łɓ������ďo�́B�iTIOCA3:CN1-16�ɃX�s�[�J�[�ڑ��v�j
//������̃��[�h�ł�S1�Ŏ�,S2�ŕ�,S3�ŕb��ύX�ł���.

#include<machine.h>
#include "iodefine.h"
#include "lcd.h"

#pragma interrupt int_imia0(vect=24)	//���荞�݊֐��̐錾

/***** define *****/

// ITU ch0�Ŏg�p���郌�W�X�^
#define TSTR  (*((volatile unsigned char *)0xFFFF60)) //ITU ch0
#define TCR0  (*((volatile unsigned char *)0xFFFF64))
#define TIER0 (*((volatile unsigned char *)0xFFFF66))
#define TSR0  (*((volatile unsigned char *)0xFFFF67))
#define GRA0  (*((volatile unsigned short *)0xFFFF6A))

// ITU ch3�Ŏg�p���郌�W�X�^
#define TCR3  (*((volatile unsigned char *)0xFFFF82))
#define TIOR3  (*((volatile unsigned char *)0xFFFF83))
//#define TIER3 (*((volatile unsigned char *)0xFFFF84))
#define TSR3  (*((volatile unsigned char *)0xFFFF85))
#define GRA3  (*((volatile unsigned short *)0xFFFF88))
#define TOER  (*((volatile unsigned char *)0xFFFF90)) 

#define P4DDR (*(volatile unsigned char *)0xFFFFC5) //P4 DIP-SW
#define P4DR  (*(volatile unsigned char *)0xFFFFC7)
#define P4PCR (*(volatile unsigned char *)0xFFFFDA)

#define P2DDR (*(volatile unsigned char *)0xFFFFC1) //P2 Push-SW
#define P2DR  (*(volatile unsigned char *)0xFFFFC3)
#define P2PCR (*(volatile unsigned char *)0xFFFFD8)

#define P5DDR (*(volatile unsigned char *)0xFFFFC8) //P5 LED
#define P5DR  (*(volatile unsigned char *)0xFFFFCA)

/****** gloval ******/
unsigned char h,m,s,count;

/******* timer0 interrupt *******/
void int_imia0(void){
	TSR0 &= ~0x01;	// �����ݔ����t���O���N���A
	count--;		// �񐔃J�E���g�ϐ���-1
	if(count==0){	// �J�E���g��0�ɂȂ�����i1�b�o�߂�����j
		if((~P2DR & 0x01) != 0x01){//DIP-SW1-ON�̃`�F�b�N
			s++;				   //ON�ł���Ύ����X�V���Ȃ�.
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
	}
	 count=50;	// �J�E���g�l�����ɖ߂�
  }
}

/********************************************************
* ���C��
********************************************************/
void main(void){

	unsigned char newstate,oldstate,ah,am;

    P4DDR = 0x00;	 //P4,2,5�|�[�g�ݒ�
    P4PCR = 0xFF;
	
	P2DDR = 0x00;
	P2PCR = 0xFF;
	
	P5DDR = 0xFF;
	
	TCR3 |= 0x23;	// ��ITU0�̐ݒ�F�����N���b�N1/8���J�E���g���AGRA3�̒l�Ŋ����ݔ���
//	TIOR3 |= 0x03;	// ��GRA�̃R���y�A�}�b�`�Ńg�O���o��
	GRA3 = 1912;    //��[�h]�̉�
	
	TCR0 |= 0x23;	  // ITU0�̐ݒ�F�����N���b�N1/8���J�E���g���AGRA0�̒l��TCNT�N���A
	GRA0 = 39999;	  // �J�E���g�l��GRA0�ɐݒ�
	TIER0 |= 0x01;	  // GRA0�Ƃ̃R���y�A�}�b�`�ɂĊ����ݗv��
//	TSTR |= 0x01;	  // ITU0�X�^�[�g
	TSTR |= 0x09;	  // ��ITU0�AITU3�X�^�[�g
	
	set_imask_ccr(0); // �����݋���(CCR)
	
	count = 50;		  // �����݉񐔂��J�E���g����ϐ���50���� �����ݎ�����1/50�i20ms�j
					  // 20ms�~50��1sec�i1�b�𐔂���j
					  
	LCD_Init();		  // LCD������
	
	
	LCD_Locate(1,0);			//�A���[���ݒ莞����2�s�ڂɕ\��.
	LCD_Putchar(ah/10+'0');		//������Ԃŕ\�������Ă���.
	LCD_Putchar(ah%10+'0');
	LCD_Putchar(':');
	LCD_Putchar(am/10+'0');
	LCD_Putchar(am%10+'0');
	
	oldstate = ~P4DR & 0xF0;
	wait(10);
	
	while(1){		    
		if((~P2DR & 0x01) == 0x01){ //���v�ݒ胂�[�h�iDIPSW b0:ON).���̃��[�h�̂Ƃ��͎��Ԃ͍X�V����Ȃ�.
			newstate = ~P4DR & 0xF0;
			wait(10);
			if(oldstate != newstate){
				if(oldstate == 0x00 && newstate == 0x10){	//S1�I�� ���@�����p
					h++;
					if(h > 23){
						h = 0;
					}
				}
				if(oldstate == 0x00 && newstate == 0x20){   //S2�I�� ���@�����p
					m++;
					if(m > 59){
						m = 0;
					}
				}
				if(oldstate == 0x00 && newstate == 0x40){   //S3�I�� �b  �����p
					s++;
					if(s > 59){
						s = 0;
					}
				}
			}
			oldstate = newstate;
		}else if((~P2DR & 0x02) == 0x02){	//�A���[���ݒ胂�[�h�iDIPSW b1:ON)
			newstate = ~P4DR & 0xF0;
			wait(10);
			if(oldstate != newstate){
				if(oldstate == 0x00 && newstate == 0x10){   //S1�I�� ���@�ݒ�p
					ah++;
					if(ah > 23){
						ah = 0;
					}
				}
				if(oldstate == 0x00 && newstate == 0x20){   //S2�I�� ���@�ݒ�p
					am++;
					if(am > 59){
						am = 0;
					}
				}				
			}
			oldstate = newstate;
			LCD_Locate(1,0);			//�A���[���ݒ莞����2�s�ڂɕ\��
			LCD_Putchar(ah/10+'0');
			LCD_Putchar(ah%10+'0');
			LCD_Putchar(':');
			LCD_Putchar(am/10+'0');
			LCD_Putchar(am%10+'0');					
		}
//�A���[��ON�̎��̏���		
		if((~P2DR & 0x04) == 0x04){	//�A���[��ON�̔���iDIPSW b2:ON)
				if(ah == h){
					if(am == m){						
						if(count <= 25){  //�w�莞���ɂȂ���.�A���[���ʒm�pP5LED��_�ł�����
							P5DR = 0x01;  //LED1�_����
							TIOR3 |= 0x03;// ��GRA�̃R���y�A�}�b�`�Ńg�O���o�� [�h]�̉����o��
						}else{
							P5DR = 0x00;  //LED1������
							TIOR3 &= 0xFC;// ��GRA�̃R���y�A�}�b�`�Ńg�O���o��OFF�@
						}
					}else{
						P5DR = 0x00;
					}
				}
		}else{	//�A���[��OFF
			P5DR = 0x00;//�ʒm�pLED����
		}
			
			LCD_Locate(0,0);	//���ԕ\��
			LCD_Putchar(h/10+'0');
			LCD_Putchar(h%10+'0');
			LCD_Putchar(':');
			LCD_Putchar(m/10+'0');
			LCD_Putchar(m%10+'0');
			LCD_Putchar(':');
			LCD_Putchar(s/10+'0');
			LCD_Putchar(s%10+'0');
			//wait(100);					
	}
}

