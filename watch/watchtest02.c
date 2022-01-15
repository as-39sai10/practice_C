//watchtest02.c
//24時間時計
//S1で時,S2で分,S3で秒を変更できる

#include<machine.h>
#include "iodefine.h"
#include "lcd.h"

#pragma interrupt int_imia0(vect=24)	//割り込み関数の宣言

/***** define *****/

// ITU ch0で使用するレジスタ
#define TSTR  (*((volatile unsigned char *)0xFFFF60))    // ITU ch0
#define TCR0  (*((volatile unsigned char *)0xFFFF64))
#define TIER0 (*((volatile unsigned char *)0xFFFF66))
#define TSR0  (*((volatile unsigned char *)0xFFFF67))
#define GRA0  (*((volatile unsigned short *)0xFFFF6A))

#define P4DDR (*(volatile unsigned char *)0xFFFFC5)
#define P4DR  (*(volatile unsigned char *)0xFFFFC7)
#define P4PCR (*(volatile unsigned char *)0xFFFFDA)


/****** gloval ******/
volatile unsigned short h,m,s,count;

/******* timer0 interrupt *******/
void int_imia0(void){
	TSR0 &= ~0x01;	// 割込み発生フラグをクリア
	count--;		// 回数カウント変数を-1
	if(count==0){	// カウントが0になったら（1秒経過したら）
		s++;
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
		count=50;	// カウント値を元に戻す
	}
}

/********************************************************
* メイン
********************************************************/
void main(void){

	unsigned char newstate,oldstate;

    P4DDR=0x00;
    P4PCR=0xFF;
	
	TCR0 |= 0x23;	  // ITU0の設定：内部クロック1/8をカウントし、GRA0とのコンペアマッチでカウンタクリア
	GRA0 = 39999;	  // カウント値をGRA0に設定
	TIER0 |= 0x01;	  // GRA0とのコンペアマッチで割込み要求
	
	set_imask_ccr(0); // 割込み使用
	
	count = 50;		  // 割込み回数をカウントする変数に50を代入 割込み周期＝1/50（20ms）
					  // 20ms×50＝1sec（1秒を数える）
	TSTR |= 0x01;	  // ITU0スタート
					  
	LCD_Init();
	
	oldstate = ~P4DR & 0xF0;//SWの情報を取得.上位4bitのみ.他はマスク.
	wait(10);//チャタリング防止
	while(1){		    
		newstate = ~P4DR & 0xF0;//SWの情報を取得.上位4bitのみ.他はマスク.
		wait(10);//チャタリング防止
		if(oldstate != newstate){						//SWの状態が変化
			if(oldstate == 0x00 && newstate == 0x10){   //S1押した時
				h++;
				if(h > 23){
					h = 0;
				}
			}
			if(oldstate == 0x00 && newstate == 0x20){	//S2押した時
				m++;
				if(m > 59){
					m = 0;
				}
			}
			if(oldstate == 0x00 && newstate == 0x40){	//S3押したとき
				s++;
				if(s > 59){
					s = 0;
				}
			}
		}
		oldstate = newstate;
		LCD_Locate(0,0);
		LCD_Putchar(h/10+'0');
		LCD_Putchar(h%10+'0');
		LCD_Putchar(':');
		LCD_Putchar(m/10+'0');
		LCD_Putchar(m%10+'0');
		LCD_Putchar(':');
		LCD_Putchar(s/10+'0');
		LCD_Putchar(s%10+'0');
	}
}

