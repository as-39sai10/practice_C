/***** toggletest02 ITU ******/
//ITUによるトグル出力
//S1オンで「ド」の音階
//S2オンで「レ」の音階
//GRAでコンペアマッチ
//TIOCA3に出力
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
	
	P4DDR = 0x00; /*ポートの初期化*/
    P4PCR = 0xFF; /*プルアップ*/
	PBDDR = 0x01; 
	
	TCR3 |= 0x23;	// ITU0の設定：内部クロック1/8をカウントし、GRA3の値で割込み発生
	TIOR3 |= 0x03;	// GRAのコンペアマッチでトグル出力
	//GRA3 = 478;		//
	
	//TSTR |= 0x01;
	
	while(1){
		if(~P4DR & 0x10){
			TOER |= 0x01;//TIOCA3端子出力許可
			GRA3 = 1912;
			TSTR |= 0x08;//タイマスタート.チャネル3
			while(~P4DR & 0x10);//スイッチがOFFになるまで鳴らす
		}else if(~P4DR & 0x20){
			TOER |= 0x01;//TIOCA3端子出力許可
			GRA3 = 1702;
			TSTR |= 0x08;//タイマスタート.チャネル3
			while(~P4DR & 0x20);//スイッチがOFFになるまで鳴らす
		}else{//スイッチがOFFのとき
		//	PBDR &= ~0x01;
			TSTR &= ~0x08;//タイマストップ
			TOER &= ~0x01;//TIOA3端子出力禁止
			PBDR &= ~0x01;//TIOA3端子出力禁止にするとI/Oポートに切り替わるため
		}				  //出力がふらつかない様0を出力しておく
		
		//TSTR |= 0x01;
	}
	
}
