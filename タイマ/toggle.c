/***** toggletest01 ITU ******/
//ITUによるトグル出力
//周波数1KHz
//周期1ms
//GRAでコンペアマッチ
//TIOCA0に出力
/***** define *****/

// ITU ch0で使用するレジスタ
#define TSTR  (*((volatile unsigned char *)0xFFFF60))    // ITU ch0
#define TCR0  (*((volatile unsigned char *)0xFFFF64))
#define TIOR0  (*((volatile unsigned char *)0xFFFF65))
//#define TIER0 (*((volatile unsigned char *)0xFFFF66))
//#define TSR0  (*((volatile unsigned char *)0xFFFF67))
#define GRA0  (*((volatile unsigned short *)0xFFFF6A))


void main(void){
	
	TCR0 |= 0x23;	// ITU0の設定：内部クロック1/8をカウントし、GRA0の値でコンペアマッチ発生
	TIOR0 |= 0x03;	// GRAのコンペアマッチでトグル出力
	GRA0 = 999;		//
	
	TSTR |= 0x01;
	
	while(1);
	
}


	