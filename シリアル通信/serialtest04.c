/***** serialtest04.c VRでデューティー比を変化させる。GRBの値をLCDとSCIで表示する ******/
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
void initSci(void);           // SCI初期化
void sndData(unsigned char);  // 1文字送信
unsigned char rcvData(void);  // 1文字受信
void show_grb0(void);         // GRB0 LCD,SCI表示

/********************************************************
* メイン
********************************************************/

//volatile unsigned char temp;
unsigned short addata;
void main( void )
{
   char *mes="DC Motor Monitor";
   
  initSci();//シリアル初期化

  LCD_Init();//LCD初期化
  
  ADCSR=0x00;//AD変換設定         
  
  			   //PWM設定
  TCR0 = 0x23; //プリスケーラ1/8,GRAによるコンペアマッチでTCNTクリア
  TMDR |= 0x01;//ch0をPWMモード
  
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
   ADCSR |= 0x20;    //AD変換スタート
   while((ADCSR & 0x80) != 0x80);  //AD変換終了チェック
   ADCSR &= ~0xA0;	//AD変換終了ビット、スタートビットを0クリア
   addata = ADDRAH;
   addata >>= 6;
   if(addata > 997){
	   addata=998;
   }
   show_grb0();
   GRB0 = addata;
   TSTR |= 0x01;   /*タイマスタート*/
  }
}


void initSci(void){
	SCR = 0x00;   
    // SCI TE,RE:clear CKE1,CKE0 = 0
	SMR = 0x00;     // データ長8ビット，ストップビット1ビット，ノンパリティ
	BRR = 51;       // 9600bps(24.56MHz)
	SCR |= 0x30;    // TIE,RIE=0,TE,RE = 1
	SSR = 0x80;     // TDRE = 1,RDRF,ORER,PER,FER:clear
}

void sndData(unsigned char data){
	while((SSR & 0x80)!=0x80);  // まだ送信データがある場合，NEWデータ転送待ち
    TDR = data;    // newデータを送信レジスタに転送
	SSR &= ~0x80;        // 送信レジスタ データありに
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