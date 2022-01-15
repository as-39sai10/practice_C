/***** itutest02 ITU ******/
#include <machine.h>

#pragma interrupt int_imia0(vect=24)	//割り込み関数の宣言
#pragma interrupt int_imia1(vect=28)

/***** define *****/
#define P5DDR (*(volatile unsigned char *)0xFFFFC8)
#define P5DR  (*(volatile unsigned char *)0xFFFFCA)
// ITU ch0で使用するレジスタ
#define TSTR  (*((volatile unsigned char *)0xFFFF60))    // ITU ch0
#define TCR0  (*((volatile unsigned char *)0xFFFF64))
#define TIER0 (*((volatile unsigned char *)0xFFFF66))
#define TSR0  (*((volatile unsigned char *)0xFFFF67))
#define GRA0  (*((volatile unsigned short *)0xFFFF6A))

#define TIOR0  (*((volatile unsigned char *)0xFFFF65))	//トグル用

// ITU ch1で使用するレジスタ
  														 // ITU ch1
#define TCR1  (*((volatile unsigned char *)0xFFFF6E))
#define TIER1 (*((volatile unsigned char *)0xFFFF70))
#define TSR1  (*((volatile unsigned char *)0xFFFF71))
#define GRA1  (*((volatile unsigned short *)0xFFFF74))

/****** global ******/
volatile unsigned short count0,count1;

/******* timer0 interrupt *******/
void int_imia0(void){
	TSR0 &= ~0x01;	// 割込み発生フラグをクリア
	count0--;
	if(count0 == 0){
		P5DR ^= 0x01;
		count0 = 50;
	} 
	
}

/******* timer1 interrupt *******/
void int_imia1(void){
	TSR1 &= ~0x01;	// 割込み発生フラグをクリア
	count1--;
	if(count1 == 0){
		P5DR ^= 0x02;
		count1 = 50;
	} 
	
}
/********************************************************
* メイン
********************************************************/
void main(void){
	P5DDR = 0xFF;	  // H8マイコンポート初期化
	
	TCR0 |= 0x23;	  // ITU0の設定：内部クロック1/8をカウントし、GRA0の値で割込み発生
	GRA0 = 39999;	  // カウント値をGRA0に設定
	TIER0 |= 0x01;	  // 割込み許可
	
	TCR1 |= 0x23;	  // ITU1の設定：内部クロック1/8をカウントし、GRA1の値で割込み発生
	GRA1 = 19999;	  // カウント値をGRA1に設定
	TIER1|= 0x01;     // 割込み許可
	
	count0 = 50;	  // 割込み回数をカウントする変数に50を代入 割込み周期＝20ms
	count1 = 50;	  // 割込み回数をカウントする変数に50を代入 割込み周期＝10ms	

	TIOR0 |= 0x03;	  //トグル出力追加（テスト用）
	
	TSTR |= 0x03; // ITU0,1 スタート
	
	set_imask_ccr(0); // 割込み許可
	
	
	P5DR = 0x00;       // LEDに初期値出力

	while(1);		  // 空ループ
	
}

