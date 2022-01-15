/***** toggletest02 ITU ******/
//ITU�ɂ��g�O���o��
//S1�I���Łu�h�v�̉��K
//S2�I���Łu���v�̉��K
//GRA�ŃR���y�A�}�b�`
//TIOCA3�ɏo��
/***** define *****/

#define PBDDR (*(volatile unsigned char *)0xFFFFD4)		//PB
#define PBDR  (*(volatile unsigned char *)0xFFFFD6)	

#define P4DDR (*(volatile unsigned char *)0xFFFFC5) 	//P4
#define P4DR  (*(volatile unsigned char *)0xFFFFC7)
#define P4PCR (*(volatile unsigned char *)0xFFFFDA)

#define TSTR  (*((volatile unsigned char *)0xFFFF60))    // ITU ch3
#define TCR3  (*((volatile unsigned char *)0xFFFF82))
#define TIOR3  (*((volatile unsigned char *)0xFFFF83))
//#define TIER3 (*((volatile unsigned char *)0xFFFF84))
#define TSR3  (*((volatile unsigned char *)0xFFFF85))
#define GRA3  (*((volatile unsigned short *)0xFFFF88))
#define TOER  (*((volatile unsigned char *)0xFFFF90)) 

void main(void){
	
	P4DDR = 0x00; /*�|�[�g�̏�����*/
    P4PCR = 0xFF; /*�v���A�b�v*/
	PBDDR = 0x01; 
	
	TCR3 |= 0x23;	// ITU0�̐ݒ�F�����N���b�N1/8���J�E���g���AGRA3�̒l�Ŋ����ݔ���
	TIOR3 |= 0x03;	// GRA�̃R���y�A�}�b�`�Ńg�O���o��
	//GRA3 = 478;		//
	
	//TSTR |= 0x01;
	
	while(1){
		if(~P4DR & 0x10){
			TOER |= 0x01;//TIOCA3�[�q�o�͋���
			GRA3 = 1912;
			TSTR |= 0x08;//�^�C�}�X�^�[�g.�`���l��3
			while(~P4DR & 0x10);//�X�C�b�`��OFF�ɂȂ�܂Ŗ炷
		}else if(~P4DR & 0x20){
			TOER |= 0x01;//TIOCA3�[�q�o�͋���
			GRA3 = 1702;
			TSTR |= 0x08;//�^�C�}�X�^�[�g.�`���l��3
			while(~P4DR & 0x20);//�X�C�b�`��OFF�ɂȂ�܂Ŗ炷
		}else{//�X�C�b�`��OFF�̂Ƃ�
		//	PBDR &= ~0x01;
			TSTR &= ~0x08;//�^�C�}�X�g�b�v
			TOER &= ~0x01;//TIOA3�[�q�o�͋֎~
			PBDR &= ~0x01;//TIOA3�[�q�o�͋֎~�ɂ����I/O�|�[�g�ɐ؂�ւ�邽��
		}				  //�o�͂��ӂ���Ȃ��l0���o�͂��Ă���
		
		//TSTR |= 0x01;
	}
	
}
