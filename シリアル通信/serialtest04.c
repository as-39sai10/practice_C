/***** serialtest04.c VR�Ńf���[�e�B�[���ω�������BGRB�̒l��LCD��SCI�ŕ\������ ******/
/***** .h .c *****/
#include "iodefine.h"
#include "lcd.h"
/***** define *****/
#define SMR (*((volatile unsigned char *)0xFFFFB8))// SCI
#define BRR (*((volatile unsigned char *)0xFFFFB9))
#define SCR (*((volatile unsigned char *)0xFFFFBA))
#define TDR (*((volatile unsigned char *)0xFFFFBB))
#define SSR (*((volatile unsigned char *)0xFFFFBC))
#define RDR (*((volatile unsigned char *)0xFFFFBD))

#define TSTR  (*(volatile unsigned char *)0xFFFF60)// ITU
#define TMDR  (*(volatile unsigned char *)0xFFFF62)
#define TCR0  (*(volatile unsigned char *)0xFFFF64)
#define GRA0  (*(volatile unsigned short *)0xFFFF6A)
#define GRB0  (*(volatile unsigned short *)0xFFFF6C)

#define ADCSR (*((volatile unsigned char *)0xFFFE8))// ADC 
#define ADDRAH (*((volatile unsigned short *)0xFFFE0))

/***** prottype *******/

/* SCI Function */
void initSci(void);           // SCI������
void sndData(unsigned char);  // 1�������M
unsigned char rcvData(void);  // 1������M
void show_grb0(void);         // GRB0 LCD,SCI�\��

/********************************************************
* ���C��
********************************************************/

//volatile unsigned char temp;
unsigned short addata;
void main( void )
{
   char *mes="DC Motor Monitor";
   
  initSci();//�V���A��������

  LCD_Init();//LCD������
  
  ADCSR=0x00;//AD�ϊ��ݒ�         
  
  			   //PWM�ݒ�
  TCR0 = 0x23; //�v���X�P�[��1/8,GRA�ɂ��R���y�A�}�b�`��TCNT�N���A
  TMDR |= 0x01;//ch0��PWM���[�h
  
  GRA0 = 999;

  while(*mes){
    sndData(*mes);
    mes++;
  }
  
  sndData('\r');
  sndData('\n');
  
  LCD_Locate(0,0);
  LCD_Putstr("GRB0: ");
  
  while(1){  
   ADCSR |= 0x20;    //AD�ϊ��X�^�[�g
   while((ADCSR & 0x80) != 0x80);  //AD�ϊ��I���`�F�b�N
   ADCSR &= ~0xA0;	//AD�ϊ��I���r�b�g�A�X�^�[�g�r�b�g��0�N���A
   addata = ADDRAH;
   addata >>= 6;
   if(addata > 997){
	   addata=998;
   }
   show_grb0();
   GRB0 = addata;
   TSTR |= 0x01;   /*�^�C�}�X�^�[�g*/
  }
}


void initSci(void){
	SCR = 0x00;   
    // SCI TE,RE:clear CKE1,CKE0 = 0
	SMR = 0x00;     // �f�[�^��8�r�b�g�C�X�g�b�v�r�b�g1�r�b�g�C�m���p���e�B
	BRR = 51;       // 9600bps(24.56MHz)
	SCR |= 0x30;    // TIE,RIE=0,TE,RE = 1
	SSR = 0x80;     // TDRE = 1,RDRF,ORER,PER,FER:clear
}

void sndData(unsigned char data){
	while((SSR & 0x80)!=0x80);  // �܂����M�f�[�^������ꍇ�CNEW�f�[�^�]���҂�
    TDR = data;    // new�f�[�^�𑗐M���W�X�^�ɓ]��
	SSR &= ~0x80;        // ���M���W�X�^ �f�[�^�����
}

unsigned char rcvData(void){

	while((SSR & 0x40)!=0x40){
		if(SSR & 0x38){
			SSR &= ~0x38;
		}
	}
	SSR &= ~0x40;

    return RDR;
}

void show_grb0(void)
{
  unsigned short n3,n2,n1;
  
  n3 = (addata / 100) + '0';
  n2 = ((addata  / 10) % 10) + '0';
  n1 = (addata % 10) + '0';
   LCD_Locate(0,5);
   LCD_Putchar(n3);
   sndData(n3);
   LCD_Locate(0,6);
   LCD_Putchar(n2);
   sndData(n2);
   LCD_Locate(0,7);
   LCD_Putchar(n1);
   sndData(n1);
   sndData('\r');
   sndData('\n');
   wait(1000);
}