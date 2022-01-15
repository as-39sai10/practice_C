/***** itutest02 ITU ******/
#include <machine.h>

#pragma interrupt int_imia0(vect=24)	//���荞�݊֐��̐錾
#pragma interrupt int_imia1(vect=28)

/***** define *****/
#define P5DDR (*(volatile unsigned char *)0xFFFFC8)
#define P5DR  (*(volatile unsigned char *)0xFFFFCA)
// ITU ch0�Ŏg�p���郌�W�X�^
#define TSTR  (*((volatile unsigned char *)0xFFFF60))    // ITU ch0
#define TCR0  (*((volatile unsigned char *)0xFFFF64))
#define TIER0 (*((volatile unsigned char *)0xFFFF66))
#define TSR0  (*((volatile unsigned char *)0xFFFF67))
#define GRA0  (*((volatile unsigned short *)0xFFFF6A))

#define TIOR0  (*((volatile unsigned char *)0xFFFF65))	//�g�O���p

// ITU ch1�Ŏg�p���郌�W�X�^
  														 // ITU ch1
#define TCR1  (*((volatile unsigned char *)0xFFFF6E))
#define TIER1 (*((volatile unsigned char *)0xFFFF70))
#define TSR1  (*((volatile unsigned char *)0xFFFF71))
#define GRA1  (*((volatile unsigned short *)0xFFFF74))

/****** global ******/
volatile unsigned short count0,count1;

/******* timer0 interrupt *******/
void int_imia0(void){
	TSR0 &= ~0x01;	// �����ݔ����t���O���N���A
	count0--;
	if(count0 == 0){
		P5DR ^= 0x01;
		count0 = 50;
	} 
	
}

/******* timer1 interrupt *******/
void int_imia1(void){
	TSR1 &= ~0x01;	// �����ݔ����t���O���N���A
	count1--;
	if(count1 == 0){
		P5DR ^= 0x02;
		count1 = 50;
	} 
	
}
/********************************************************
* ���C��
********************************************************/
void main(void){
	P5DDR = 0xFF;	  // H8�}�C�R���|�[�g������
	
	TCR0 |= 0x23;	  // ITU0�̐ݒ�F�����N���b�N1/8���J�E���g���AGRA0�̒l�Ŋ����ݔ���
	GRA0 = 39999;	  // �J�E���g�l��GRA0�ɐݒ�
	TIER0 |= 0x01;	  // �����݋���
	
	TCR1 |= 0x23;	  // ITU1�̐ݒ�F�����N���b�N1/8���J�E���g���AGRA1�̒l�Ŋ����ݔ���
	GRA1 = 19999;	  // �J�E���g�l��GRA1�ɐݒ�
	TIER1|= 0x01;     // �����݋���
	
	count0 = 50;	  // �����݉񐔂��J�E���g����ϐ���50���� �����ݎ�����20ms
	count1 = 50;	  // �����݉񐔂��J�E���g����ϐ���50���� �����ݎ�����10ms	

	TIOR0 |= 0x03;	  //�g�O���o�͒ǉ��i�e�X�g�p�j
	
	TSTR |= 0x03; // ITU0,1 �X�^�[�g
	
	set_imask_ccr(0); // �����݋���
	
	
	P5DR = 0x00;       // LED�ɏ����l�o��

	while(1);		  // �󃋁[�v
	
}

