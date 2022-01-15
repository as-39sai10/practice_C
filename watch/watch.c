//watchtest01.c
//システム起動時からの時間経過を表示するプログラム
//ただし23:59:59までとする

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

	TCR0 |= 0x23;	  // ITU0の設定：内部クロック1/8をカウントし、GRA0とのコンペアマッチでカウンタクリア
	GRA0 = 39999;	  // カウント値をGRA0に設定
	TIER0 |= 0x01;	  // GRA0とのコンペアマッチで割込み要求
	set_imask_ccr(0); // 割込み使用
	
	count = 50;		  // 割込み回数をカウントする変数に50を代入 割込み周期＝1/50（20ms）
					  // 20ms×50＝1sec（1秒を数える）
	TSTR |= 0x01;	  // ITU0スタート			  
	
	LCD_Init();

	while(1){		    
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

