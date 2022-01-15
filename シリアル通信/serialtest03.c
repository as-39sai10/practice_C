/***** serialtest03.c PC->H8 �����񑗐M LCD�\�� ******/
/***** .h .c *****/
#include "iodefine.h"
#include "lcd.h"
/***** define *****/
#define SMR (*((volatile unsigned char *)0xFFFFB8))     // 8�r�b�g�A�N�Z�X�ichar�j
#define BRR (*((volatile unsigned char *)0xFFFFB9))
#define SCR (*((volatile unsigned char *)0xFFFFBA))
#define TDR (*((volatile unsigned char *)0xFFFFBB))
#define SSR (*((volatile unsigned char *)0xFFFFBC))
#define RDR (*((volatile unsigned char *)0xFFFFBD))

/***** prottype *******/

/* SCI Function */
void initSci(void);           // SCI������
void sndData(unsigned char);  // 1�������M
unsigned char rcvData(void);  //1������M

/********************************************************
* ���C��
********************************************************/

void main( void )
{
   char x,y;
   char a;
   char *mes="Hello! H8\n";
  
  
  initSci();//�V���A���|�[�g������
  
  
  LCD_Init();//LCD������

  while(*mes){
    sndData(*mes);
    mes++;
  }
  
  LCD_Locate(0,0);//�\���ʒu�Z�b�g
  
  x=y=0;//x(col) y(row)
  
  while(1){                     
    a=rcvData();//1������M
    sndData(a); //1�������M
	
	LCD_Putchar(a);//LCD�\��
    x++;
    if(x > 15){	//col �������`�F�b�N
      x = 0;
      y++;
      if(y > 1){ //row �s���`�F�b�N
        y = 0;
        LCD_Clr(); //��ʃN���A
      }
    }
    LCD_Locate(y,x); //�\���ʒu�Đݒ�
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