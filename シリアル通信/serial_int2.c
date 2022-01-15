/***** serialtest01 エコーバック  ******/				
/***** .h .c *****/				
				
#include "iodefine.h"				
#include "lcd.h"				
				
#pragma interrupt INT_RXI1(vect=57)				
				
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
				
//void wait(unsigned short w);				
				
//****** RXD1 受信割込み ***********				
void INT_RXI1(void){			//H8実習基板ではRXD1（チャネル１）使用	
	char a;			
 	a=rcvData();				//PC(ｷｰﾎﾞｰﾄﾞ）⇒H8マイコンへ	
 	sndData(a);					//H8ﾏｲｺﾝ ⇒ PC（画面）へ	
}				


//****** メイン処理 ***********				
void main( void )				
{				
  				
   char *mes="Hello! H8";				
  				
	initSci();	//シリアルポート初期化		
	LCD_Init(); //LCD初期化			
				
	LCD_Locate(0,0);			
				
	SCR |= 0x40;    // RIE = 1			
				
  while(*mes){				
    sndData(*mes);		//初期メッセージ送信		
	LCD_Putchar(*mes);			
    mes++;				
  }				
  				
  while(1);	 //無限ループ　（受信割込み待ち）			
  				
}				
				
				
//****** シリアル初期化関数 ***********				
void initSci(void){				
	SCR = 0x00;   			
                    // SCI TE,RE:clear CKE1,CKE0 = 0				
	SMR = 0x00;     // データ長8ビット，ストップビット1ビット，ノンパリティ			
	BRR = 51;       // 9600bps			
	SCR |= 0x30;    // TIE,RIE=0,TE,RE = 1			
	//SCR |= 0xF0;    // TIE,RIE=0,TE,RE = 1			
	SSR |= 0x84;     // TDRE = 1,RDRF,ORER,PER,FER:clear			
}				
				
//****** シリアル送信関数 ***********				
void sndData(unsigned char data){				
				
   while((SSR & 0x80)!=0x80);  // まだ送信データがある場合，NEWデータ転送待ち				
   TDR = data;                 // newデータを送信レジスタに転送				
   SSR &= ~0x80;               // 送信レジスタ データありに				
}				
				
//****** シリアル受信関数 ***********				
unsigned char rcvData(void){				
				
//	while((SSR & 0x40)!=0x40){ //受信待ち			
//		if(SSR & 0x38){        //エラーチェック		
//			SSR &= ~0x38;      //エラーフラグ消去	
//		}		
//	}			
				
	SSR &= ~0x40;			
				
    return RDR;				
}				
