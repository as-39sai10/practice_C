//inttest01.c IRQ0

/*****.h .c***********/
#include <machine.h>		//#include "machine.h"でもOK
//#include "machine.h"

#pragma interrupt int_irq0(vect=12)		//割り込み関数の宣言★

/***** port def ******/
#define P1DDR (*(volatile unsigned char *)0xFFFFC0)
#define P1DR  (*(volatile unsigned char *)0xFFFFC2)
#define P5DDR (*(volatile unsigned char *)0xFFFFC8)
#define P5DR  (*(volatile unsigned char *)0xFFFFCA)
//割込み
#define ISCR  (*(volatile unsigned char *)0xFFFFF4)
#define IER   (*(volatile unsigned char *)0xFFFFF5)
#define ISR   (*(volatile unsigned char *)0xFFFFF6)

/*----- prttype def -----*/
void wait(unsigned short);	// プロトタイプ宣言

/*+++++++++++++++++++++++++++*/
/****** main ******/
void int_irq0(void)            //割り込み関数★
{
    unsigned short cnt;
    cnt=3;
    while(cnt--){                //3回繰り返し
        P5DR = 0x03;
        wait(1000);
        P5DR = 0x00;
        wait(1000);
    }
    ISR &= ~0x01;//割り込みフラグクリア
}

void main(void)
{
   unsigned short leddata;
   
   P1DDR=0xFF;                //ポート1初期化
   
   leddata=1;
   /*割込み設定*/ 
   
    ISCR |= 0x01;              //入力の立ち下がりエッジで割り込み要求発生
    IER |= 0x01;               //IRQ0割り込みを許可
    P5DDR = 0xFF;              //P5を全ビット出力に設定
    set_imask_ccr(0);          //割り込み許可
    while (1) {                //繰り返し実行
      P1DR=~leddata;           //順次点灯処理
      leddata<<=1;
    
      if(leddata>128){
        leddata=1;
      }
    
      wait(500);
    }
}

/*----- function -----*/
void wait(unsigned short w){
  //volatile unsigned short i,j;
    unsigned short i,j;
   
  for(i=0;i<w;i++){            //w*1ms
  	for(j=0;j<2000;j++){   //1ms
    }
  }
}