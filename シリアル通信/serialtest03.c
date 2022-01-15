/***** serialtest03.c PC->H8 文字列送信 LCD表示 ******/
/***** .h .c *****/
#include "iodefine.h"
#include "lcd.h"
/***** define *****/
#define SMR (*((volatile unsigned char *)0xFFFFB8))     // 8ビットアクセス（char）
#define BRR (*((volatile unsigned char *)0xFFFFB9))
#define SCR (*((volatile unsigned char *)0xFFFFBA))
#define TDR (*((volatile unsigned char *)0xFFFFBB))
#define SSR (*((volatile unsigned char *)0xFFFFBC))
#define RDR (*((volatile unsigned char *)0xFFFFBD))

/***** prottype *******/

/* SCI Function */
void initSci(void);           // SCI初期化
void sndData(unsigned char);  // 1文字送信
unsigned char rcvData(void);  //1文字受信

/********************************************************
* メイン
********************************************************/

void main( void )
{
   char x,y;
   char a;
   char *mes="Hello! H8\n";
  
  
  initSci();//シリアルポート初期化
  
  
  LCD_Init();//LCD初期化

  while(*mes){
    sndData(*mes);
    mes++;
  }
  
  LCD_Locate(0,0);//表示位置セット
  
  x=y=0;//x(col) y(row)
  
  while(1){                     
    a=rcvData();//1文字受信
    sndData(a); //1文字送信
	
	LCD_Putchar(a);//LCD表示
    x++;
    if(x > 15){	//col 文字数チェック
      x = 0;
      y++;
      if(y > 1){ //row 行数チェック
        y = 0;
        LCD_Clr(); //画面クリア
      }
    }
    LCD_Locate(y,x); //表示位置再設定
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