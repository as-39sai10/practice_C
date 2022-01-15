/***** itutest01 ITU ******/
#include <machine.h>

#pragma interrupt int_imia0(vect=24)	//���荞�݊֐��̐錾

/***** define *****/
#define P1DDR (*(volatile unsigned char *)0xFFFFC0)
#define P1DR  (*(volatile unsigned char *)0xFFFFC2)
// ITU ch0�Ŏg�p���郌�W�X�^
#define TSTR  (*((volatile unsigned char *)0xFFFF60))    // ITU ch0
#define TCR0  (*((volatile unsigned char *)0xFFFF64))
#define TIER0 (*((volatile unsigned char *)0xFFFF66))
#define TSR0  (*((volatile unsigned char *)0xFFFF67))
#define GRA0  (*((volatile unsigned short *)0xFFFF6A))

/****** gloval ******/
volatile unsigned short count,led;

/******* timer0 interrupt *******/
void int_imia0(void){
	TSR0 &= ~0x01;	// �����ݔ����t���O���N���A
	count--;		// �񐔃J�E���g�ϐ���-1
	if(count==0){	// �J�E���g��0�ɂȂ�����i1�b�o�߂�����j
		led++;		// LED�ɕ\������ϐ���+1
		P1DR = ~led;	// ���̒l��LED�ɏo��
		count=50;	// �J�E���g�l�����ɖ߂�
	}
}

/********************************************************
* ���C��
********************************************************/
void main(void){
	P1DDR = 0xFF;	  // H8�}�C�R���|�[�g������
	TCR0 = 0x23;	  // ITU0�̐ݒ�F�����N���b�N1/8���J�E���g���AGRA0�̒l�Ŋ����ݔ���
	GRA0 = 39999;	  // �J�E���g�l��GRA0�ɐݒ�
	TIER0 |= 0x01;	  // �����݋���
	TSTR |= 0x01;	  // ITU0�X�^�[�g
	set_imask_ccr(0); // �����ݎg�p
	count = 50;		  // �����݉񐔂��J�E���g����ϐ���50���� �����ݎ�����1/50�i20ms�j
					  // 20ms�~50��1sec�i1�b�𐔂���j
	led = 0x00;		  // LED�ɕ\�����鏉���l�i0x00�j
	P1DR = ~led;      // LED�ɏo��

	while(1){		    // �󃋁[�v
	}
}

