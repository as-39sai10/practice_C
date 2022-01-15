//inttest03.c IRQ0 & NMI

/*****.h .c***********/
#include <machine.h>

#pragma interrupt int_nmi(vect=7)	//���荞�݊֐��̐錾��
#pragma interrupt int_irq0(vect=12)	//���荞�݊֐��̐錾��

/***** port def ******/
#define P1DDR (*(volatile unsigned char *)0xFFFFC0)
#define P1DR  (*(volatile unsigned char *)0xFFFFC2)
#define P5DDR (*(volatile unsigned char *)0xFFFFC8)
#define P5DR  (*(volatile unsigned char *)0xFFFFCA)
//������
#define SYSC  (*(volatile unsigned char *)0xFFFFF2)
#define ISCR  (*(volatile unsigned char *)0xFFFFF4)
#define IER   (*(volatile unsigned char *)0xFFFFF5)
#define ISR   (*(volatile unsigned char *)0xFFFFF6)

/*----- prttype def -----*/
void wait(unsigned short);	// �v���g�^�C�v�錾

/*+++++++++++++++++++++++++++*/
/****** main ******/
void int_nmi(void)            //���荞�݊֐���
{
    unsigned short cnt;
    cnt=3;
    while(cnt--){                //3��J��Ԃ�
        P5DR = 0x03;
        wait(1000);
        P5DR = 0x00;
        wait(1000);
    }
}

void int_irq0(void)            //���荞�݊֐���
{
    unsigned short cnt;
    cnt=3;
    while(cnt--){                //3��J��Ԃ�
        P5DR = 0x01;
        wait(1000);
        P5DR = 0x02;
        wait(1000);
    }
    ISR &= ~0x01;//���荞�݃t���O�N���A
}

void main(void)
{
   unsigned short leddata;
   leddata=1;
   
   P1DDR=0xFF;                //�|�[�g1������
   P5DDR = 0xFF;              //P5��S�r�b�g�o�͂ɐݒ�
   
   SYSC |= 0x00;              //NMI���̗͂���������G�b�W�Ŋ��荞�ݗv������
   ISCR |= 0x01;              //IRQ0���̗͂���������G�b�W�Ŋ��荞�ݗv������
   IER |= 0x01;               //IRQ0���荞�݂�����
   
   set_imask_ccr(0);          //���荞�݋���
    
	while (1) {               //�J��Ԃ����s
      P1DR=~leddata;          //�����_������
      leddata<<=1;
    
      if(leddata>128){
        leddata=1;
      }
    
      wait(500);
    }
}

/*----- function -----*/
void wait(unsigned short w){
  //volatile unsigned short i,j;
    unsigned short i,j;
   
  for(i=0;i<w;i++){            //w*1ms
  	for(j=0;j<2000;j++){   //1ms
    }
  }
}