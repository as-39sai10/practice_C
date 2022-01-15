/***** itutest01 ITU ******/
#include <machine.h>

#pragma interrupt int_imia0(vect=24)	//割り込み関数の宣言

/***** define *****/
#define P1DDR (*(volatile unsigned char *)0xFFFFC0)
#define P1DR  (*(volatile unsigned char *)0xFFFFC2)
// ITU ch0で使用するレジスタ
#define TSTR  (*((volatile unsigned char *)0xFFFF60))    // ITU ch0
#define TCR0  (*((volatile unsigned char *)0xFFFF64))
#define TIER0 (*((volatile unsigned char *)0xFFFF66))
#define TSR0  (*((volatile unsigned char *)0xFFFF67))
#define GRA0  (*((volatile unsigned short *)0xFFFF6A))

/****** gloval ******/
volatile unsigned short count,led;

/******* timer0 interrupt *******/
void int_imia0(void){
	TSR0 &= ~0x01;	// 割込み発生フラグをクリア
	count--;		// 回数カウント変数を-1
	if(count==0){	// カウントが0になったら（1秒経過したら）
		led++;		// LEDに表示する変数を+1
		P1DR = ~led;	// その値をLEDに出力
		count=50;	// カウント値を元に戻す
	}
}

/********************************************************
* メイン
********************************************************/
void main(void){
	P1DDR = 0xFF;	  // H8マイコンポート初期化
	TCR0 = 0x23;	  // ITU0の設定：内部クロック1/8をカウントし、GRA0の値で割込み発生
	GRA0 = 39999;	  // カウント値をGRA0に設定
	TIER0 |= 0x01;	  // 割込み許可
	TSTR |= 0x01;	  // ITU0スタート
	set_imask_ccr(0); // 割込み使用
	count = 50;		  // 割込み回数をカウントする変数に50を代入 割込み周期＝1/50（20ms）
					  // 20ms×50＝1sec（1秒を数える）
	led = 0x00;		  // LEDに表示する初期値（0x00）
	P1DR = ~led;      // LEDに出力

	while(1){		    // 空ループ
	}
}

