/***** serialtest01 �G�R�[�o�b�N  ******/
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

//void wait(unsigned short w);

/********************************************************
* ���C��
********************************************************/

//volatile unsigned char temp;

void main( void )
{
  
   char a;
   char *mes="Hello! H8";

//  ��L������������Ƃ����Ȃ�   
//   char *mes;			
//   char str[10]="Hello! H8";
//   mes=str;
   
	initSci();	//�V���A���|�[�g������
	LCD_Init(); //LCD������
	
	LCD_Locate(0,0);
	
	
  while(*mes){
  	sndData(*mes);	//�������b�Z�[�W���M
	LCD_Putchar(*mes);
    mes++;
  }
  
  while(1){                     
    a=rcvData();	//�G�R�[�o�b�N����
    sndData(a);
  }
}

void initSci(void){
	SCR = 0x00;   
                    // SCI TE,RE:clear CKE1,CKE0 = 0
	SMR = 0x00;     // �f�[�^��8�r�b�g�C�X�g�b�v�r�b�g1�r�b�g�C�m���p���e�B
	BRR = 51;       // 9600bps
	SCR |= 0x30;    // TIE,RIE=0,TE,RE = 1
	//SCR |= 0xF0;    // TIE,RIE=0,TE,RE = 1
	SSR = 0x80;     // TDRE = 1,RDRF,ORER,PER,FER:clear
}

void sndData(unsigned char data){

   while((SSR & 0x80)!=0x80);  // �܂����M�f�[�^������ꍇ�CNEW�f�[�^�]���҂�
   TDR = data;                 // new�f�[�^�𑗐M���W�X�^�ɓ]��
   SSR &= ~0x80;               // ���M���W�X�^ �f�[�^�����
}

unsigned char rcvData(void){
	
	while((SSR & 0x40)!=0x40){ //��M�҂�
		if(SSR & 0x38){        //�G���[�`�F�b�N
			SSR &= ~0x38;      //�G���[�t���O����
		}
	}

	SSR &= ~0x40;				//��M�҂���Ԃɐݒ�

    return RDR;					//��M�f�[�^�ԋp
}
