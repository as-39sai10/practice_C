//watchtest03.c
//24時間時計
//DIP-SWの1をオンにすることでセッティングモードに移行.時計がストップする.
//DIP-SWの2をオンにすることでアラームモードに移行.
//DIP-SWの3をオンにすることでアラームオン.アラーム設定時刻になるとP5のLED1が点滅.
//☆（追加）　 〃　　　　　　ブザー出力[ド]の音をLED点滅に同期して出力。（TIOCA3:CN1-16にスピーカー接続要）
//いずれのモードでもS1で時,S2で分,S3で秒を変更できる.

#include<machine.h>
#include "iodefine.h"
#include "lcd.h"

#pragma interrupt int_imia0(vect=24)	//割り込み関数の宣言

/***** define *****/

// ITU ch0で使用するレジスタ
#define TSTR  (*((volatile unsigned char *)0xFFFF60)) //ITU ch0
#define TCR0  (*((volatile unsigned char *)0xFFFF64))
#define TIER0 (*((volatile unsigned char *)0xFFFF66))
#define TSR0  (*((volatile unsigned char *)0xFFFF67))
#define GRA0  (*((volatile unsigned short *)0xFFFF6A))

// ITU ch3で使用するレジスタ
#define TCR3  (*((volatile unsigned char *)0xFFFF82))
#define TIOR3  (*((volatile unsigned char *)0xFFFF83))
//#define TIER3 (*((volatile unsigned char *)0xFFFF84))
#define TSR3  (*((volatile unsigned char *)0xFFFF85))
#define GRA3  (*((volatile unsigned short *)0xFFFF88))
#define TOER  (*((volatile unsigned char *)0xFFFF90)) 

#define P4DDR (*(volatile unsigned char *)0xFFFFC5) //P4 DIP-SW
#define P4DR  (*(volatile unsigned char *)0xFFFFC7)
#define P4PCR (*(volatile unsigned char *)0xFFFFDA)

#define P2DDR (*(volatile unsigned char *)0xFFFFC1) //P2 Push-SW
#define P2DR  (*(volatile unsigned char *)0xFFFFC3)
#define P2PCR (*(volatile unsigned char *)0xFFFFD8)

#define P5DDR (*(volatile unsigned char *)0xFFFFC8) //P5 LED
#define P5DR  (*(volatile unsigned char *)0xFFFFCA)

/****** gloval ******/
unsigned char h,m,s,count;

/******* timer0 interrupt *******/
void int_imia0(void){
	TSR0 &= ~0x01;	// 割込み発生フラグをクリア
	count--;		// 回数カウント変数を-1
	if(count==0){	// カウントが0になったら（1秒経過したら）
		if((~P2DR & 0x01) != 0x01){//DIP-SW1-ONのチェック
			s++;				   //ONであれば時刻更新しない.
			if(s > 59){
				s = 0;
				m++;
				if(m > 59){
					m = 0;
					h++;
					if(h > 23){
						h = 0;
					}
				}
			}
	}
	 count=50;	// カウント値を元に戻す
  }
}

/********************************************************
* メイン
********************************************************/
void main(void){

	unsigned char newstate,oldstate,ah,am;

    P4DDR = 0x00;	 //P4,2,5ポート設定
    P4PCR = 0xFF;
	
	P2DDR = 0x00;
	P2PCR = 0xFF;
	
	P5DDR = 0xFF;
	
	TCR3 |= 0x23;	// ☆ITU0の設定：内部クロック1/8をカウントし、GRA3の値で割込み発生
//	TIOR3 |= 0x03;	// ☆GRAのコンペアマッチでトグル出力
	GRA3 = 1912;    //☆[ド]の音
	
	TCR0 |= 0x23;	  // ITU0の設定：内部クロック1/8をカウントし、GRA0の値でTCNTクリア
	GRA0 = 39999;	  // カウント値をGRA0に設定
	TIER0 |= 0x01;	  // GRA0とのコンペアマッチにて割込み要求
//	TSTR |= 0x01;	  // ITU0スタート
	TSTR |= 0x09;	  // ☆ITU0、ITU3スタート
	
	set_imask_ccr(0); // 割込み許可(CCR)
	
	count = 50;		  // 割込み回数をカウントする変数に50を代入 割込み周期＝1/50（20ms）
					  // 20ms×50＝1sec（1秒を数える）
					  
	LCD_Init();		  // LCD初期化
	
	
	LCD_Locate(1,0);			//アラーム設定時刻を2行目に表示.
	LCD_Putchar(ah/10+'0');		//初期状態で表示させておく.
	LCD_Putchar(ah%10+'0');
	LCD_Putchar(':');
	LCD_Putchar(am/10+'0');
	LCD_Putchar(am%10+'0');
	
	oldstate = ~P4DR & 0xF0;
	wait(10);
	
	while(1){		    
		if((~P2DR & 0x01) == 0x01){ //時計設定モード（DIPSW b0:ON).このモードのときは時間は更新されない.
			newstate = ~P4DR & 0xF0;
			wait(10);
			if(oldstate != newstate){
				if(oldstate == 0x00 && newstate == 0x10){	//S1オン 時　調整用
					h++;
					if(h > 23){
						h = 0;
					}
				}
				if(oldstate == 0x00 && newstate == 0x20){   //S2オン 分　調整用
					m++;
					if(m > 59){
						m = 0;
					}
				}
				if(oldstate == 0x00 && newstate == 0x40){   //S3オン 秒  調整用
					s++;
					if(s > 59){
						s = 0;
					}
				}
			}
			oldstate = newstate;
		}else if((~P2DR & 0x02) == 0x02){	//アラーム設定モード（DIPSW b1:ON)
			newstate = ~P4DR & 0xF0;
			wait(10);
			if(oldstate != newstate){
				if(oldstate == 0x00 && newstate == 0x10){   //S1オン 時　設定用
					ah++;
					if(ah > 23){
						ah = 0;
					}
				}
				if(oldstate == 0x00 && newstate == 0x20){   //S2オン 分　設定用
					am++;
					if(am > 59){
						am = 0;
					}
				}				
			}
			oldstate = newstate;
			LCD_Locate(1,0);			//アラーム設定時刻を2行目に表示
			LCD_Putchar(ah/10+'0');
			LCD_Putchar(ah%10+'0');
			LCD_Putchar(':');
			LCD_Putchar(am/10+'0');
			LCD_Putchar(am%10+'0');					
		}
//アラームONの時の処理		
		if((~P2DR & 0x04) == 0x04){	//アラームONの判定（DIPSW b2:ON)
				if(ah == h){
					if(am == m){						
						if(count <= 25){  //指定時刻になった.アラーム通知用P5LEDを点滅させる
							P5DR = 0x01;  //LED1点灯●
							TIOR3 |= 0x03;// ☆GRAのコンペアマッチでトグル出力 [ド]の音を出力
						}else{
							P5DR = 0x00;  //LED1消灯○
							TIOR3 &= 0xFC;// ☆GRAのコンペアマッチでトグル出力OFF　
						}
					}else{
						P5DR = 0x00;
					}
				}
		}else{	//アラームOFF
			P5DR = 0x00;//通知用LED消灯
		}
			
			LCD_Locate(0,0);	//時間表示
			LCD_Putchar(h/10+'0');
			LCD_Putchar(h%10+'0');
			LCD_Putchar(':');
			LCD_Putchar(m/10+'0');
			LCD_Putchar(m%10+'0');
			LCD_Putchar(':');
			LCD_Putchar(s/10+'0');
			LCD_Putchar(s%10+'0');
			//wait(100);					
	}
}

