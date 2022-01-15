/***** toggletest01 ITU ******/
//ITU�ɂ��g�O���o��
//���g��1KHz
//����1ms
//GRA�ŃR���y�A�}�b�`
//TIOCA0�ɏo��
/***** define *****/

// ITU ch0�Ŏg�p���郌�W�X�^
#define TSTR  (*((volatile unsigned char *)0xFFFF60))    // ITU ch0
#define TCR0  (*((volatile unsigned char *)0xFFFF64))
#define TIOR0  (*((volatile unsigned char *)0xFFFF65))
//#define TIER0 (*((volatile unsigned char *)0xFFFF66))
//#define TSR0  (*((volatile unsigned char *)0xFFFF67))
#define GRA0  (*((volatile unsigned short *)0xFFFF6A))


void main(void){
	
	TCR0 |= 0x23;	// ITU0�̐ݒ�F�����N���b�N1/8���J�E���g���AGRA0�̒l�ŃR���y�A�}�b�`����
	TIOR0 |= 0x03;	// GRA�̃R���y�A�}�b�`�Ńg�O���o��
	GRA0 = 999;		//
	
	TSTR |= 0x01;
	
	while(1);
	
}


	