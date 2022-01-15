/*---------------習得度測定 エアコンを想定したプログラム(ver C言語)---------------*/



#include "iodefine.h"
#include "lcd.h"
#include <machine.h>

//割り込み関数
#pragma interrupt int_ADI(vect=60)                      //AD割り込み用
#pragma interrupt INT_IMIA3(vect=36)                    //時計用

//AD変換用
#define ADCSR (*(volatile unsigned char *)0xFFFFE8)
#define ADDRA (*(volatile unsigned short *)0xFFFFE0)

#define TSTR  (*(volatile unsigned char *)0xFFFF60)
#define TMDR  (*(volatile unsigned char *)0xFFFF62)

//PWM0 red
#define TCR0  (*(volatile unsigned char *)0xFFFF64)
#define GRA0  (*(volatile unsigned short *)0xFFFF6A)
#define GRB0  (*(volatile unsigned short *)0xFFFF6C)

//PWM1 blue
#define TCR1  (*(volatile unsigned char *)0xFFFF6E)
#define GRA1  (*(volatile unsigned short *)0xFFFF74)
#define GRB1  (*(volatile unsigned short *)0xFFFF76)

//PWM2 モーター
#define TCR2  (*(volatile unsigned char *)0xFFFF78)
#define GRA2  (*(volatile unsigned short *)0xFFFF7E)
#define GRB2  (*(volatile unsigned short *)0xFFFF80)

// １秒用
#define TCR3  (*(volatile unsigned char *)0xFFFF82)
#define TIER3 (*(volatile unsigned char *)0xFFFF84)
#define TSR3  (*(volatile unsigned char *)0xFFFF85)
#define GRA3  (*(volatile unsigned short *)0xFFFF88)


//ポート１のLED用
#define P1DDR (*(volatile unsigned char *)0xFFFFC0)
#define P1DR  (*(volatile unsigned char *)0xFFFFC2)

//お休みタイマー設定用SW
#define P4DDR (*(volatile unsigned char *)0xFFFFC5)
#define P4DR  (*(volatile unsigned char *)0xFFFFC7)
#define P4PCR (*(volatile unsigned char *)0xFFFFDA)

//DIP
#define P2DDR  (*(volatile unsigned char *)0xFFFFC1)
#define P2DR  (*(volatile unsigned char *)0xFFFFC3)
#define P2PCR  (*(volatile unsigned char *)0xFFFFD8)

//シリアル通信用
#define SMR (*((volatile unsigned char *)0xFFFFB8))     // 8ビットアクセス（char）
#define BRR (*((volatile unsigned char *)0xFFFFB9))
#define SCR (*((volatile unsigned char *)0xFFFFBA))
#define TDR (*((volatile unsigned char *)0xFFFFBB))
#define SSR (*((volatile unsigned char *)0xFFFFBC))
#define RDR (*((volatile unsigned char *)0xFFFFBD))

//プロトタイプ

void math_ondo(void);         //温度計算関数
void math_tokei(void);        //時計
void ondo_30(void);
void ondo_28_30(void);
void ondo_28u(void);
void tokei_set(void);
void INT_IMIA3(void);
void initSci(void);           // SCI初期化
void sndData(unsigned char);  // 1文字送信
unsigned char rcvData(void);  //1文字受信

//グローバル宣言
volatile unsigned short str[17];           //温度表示用

volatile unsigned short sta[17];           //時計用
volatile unsigned char  sec;
volatile unsigned char  min;
volatile unsigned char  hou;
volatile unsigned short count;

volatile unsigned short ad_data;           //AD変換格納用


/*---------------ここからメイン---------------*/
void main(void)
{
//	unsigned char newstate,oldstate;
	
	
	P1DDR = 0xFF;       /* ポート初期化 */
    P1DR = ~0x00;       //初期点灯データ
	P2PCR = 0xFF;       //プルアップ有効
    P2DDR = 0x00;	
    P4PCR = 0xFF;       //プルアップ有効
	P4DDR = 0x00;
	
	
	TMDR |= 0x07;		//ch0,1,2をPWMモード	
	
	TCR0 = 0x23; 		//プリスケーラ1/8
	TCR1 = 0x23; 		//プリスケーラ1/8
	TCR2 = 0x23; 		//プリスケーラ1/8
	TCR3 = 0x23; 		//プリスケーラ1/8
	
	TIER3 |= 0x01;	  // 割込み許可
    
	LCD_Init();                   //LCD初期化
	initSci();	        //シリアルポート初期化
	set_imask_ccr(0);
	
	GRA0 = 1023;        //GRAに初期値を格納 赤の値      
		
	GRA1 = 1023;        //GRAに初期値を格納 青の値     
	
	GRA2 = 999;         //GRAに初期値を格納 モーター用
	
	GRA3 = 39999;         //GRAに初期値を格納 1s用
	
	count = 9;
	
    ADCSR |= 0x60;      //AD変換初期設定
	
	TSTR |= 0x0F;       //全タイマスタート
	
	
	
	
	while(1)
	{  
			   	
	  //---------------時刻設定用---------------//	   
	   if((~P2DR & 0x01) == 0x01)
	   { 
		  TSTR &= 0x00;
		  tokei_set();
		}
		 
	   if(~P4DR & 0x80){  TSTR |= 0x0F;	 }
	   
	  //---------------温度状態用LED---------------//		
	   GRB0 = (ADDRA  >> 6);		//熱いほど赤く光る
	   GRB1 = (~ADDRA  >> 6);		//寒いほど青く光る
	  
	   
	   //---------------モーターの処理---------------//
	   ad_data = (ADDRA  >> 6); 
	//30℃以上の場合
		if(ad_data >= 625 || ad_data > 999)
		{
			ondo_30();			
		}
	//28℃以上30未満の場合
		if(ad_data >= 574 && ad_data < 625)
		{
			ondo_28_30();			
		}
	//28℃未満の場合
		if(ad_data < 574)
		{
			ondo_28u();
		}		
		
	}
	
}

/*---------------メイン終了---------------*/

//LCD設定
void int_ADI(void)
{
	    ADCSR &= ~0x80;
		
		math_ondo();
		math_tokei();
		
				
		LCD_Locate(0,0);
		LCD_Putstr("@=");
		LCD_Putchar(str[2]);      //1桁目の文字    	
    	LCD_Putchar(str[4]);      //小数点第1位の文字
		LCD_Putchar('.');         //小数点
    	LCD_Putchar(str[5]);      //小数第2位の文字
    	LCD_Putchar(str[6]);      //小数第3位の文字
		LCD_Putchar(128+95);          //゜の文字
    	LCD_Putchar('C');         //Vの文字
		
		
	//モーターの状態用 回転速度により表示する文字が変わる	
		LCD_Locate(0,11);
		LCD_Putchar(str[11]);
		LCD_Putchar(str[12]);
		LCD_Putchar(str[13]);
		LCD_Putchar(str[14]);
		
	
		
	    LCD_Locate(1,0);
		LCD_Putchar(sta[0]);      //時間　10の位    	
    	LCD_Putchar(sta[1]);      //時間　1の位
		LCD_Putchar(':');
		LCD_Putchar(sta[3]);      //分　10の位    	
    	LCD_Putchar(sta[4]);      //分　1の位
		LCD_Putchar(':');
		LCD_Putchar(sta[6]);      //秒　10の位   	
    	LCD_Putchar(sta[7]);      //秒　1の位
		
		
		LCD_Locate(1,11);
		LCD_Putchar(sta[11]);
		LCD_Putchar(sta[12]);
		LCD_Putchar(sta[13]);
		LCD_Putchar(sta[14]);
		
		ADCSR |= 0x20;
		
		
}
/*---------------LCD設定　終了---------------*/



/*---------------1秒用---------------*/
void INT_IMIA3(void)
{
	TSR3 &= ~0x01;	// 割込み発生フラグをクリア
	count--;		// 回数カウント変数を-1
	if(count==0)
	{	
		sec++;
		if(sec > 59 )
		{
			sec = 0;
			min++;
		}
		if(min > 59 )
		{
			min = 0;
			hou++;
		}
		if(hou > 23 )
		{
			hou = 0;
		}
		
		count = 9;
				
	}
	
 }       



//温度計算関数
void math_ondo(void)
{
   //温度用 約00.00℃〜50.00まで
		str[6] = '0' + (int) ( ( (ADDRA  >> 6) * 0.0048)  * 1000) % 10;
		if(str[6] > '9'){str[6] = '0';}
		
		str[5] = '0' + (int)  ( ( (ADDRA  >> 6) * 0.0048) * 100) % 10;
		if(str[5] > '9'){str[5] = '0';}
		
		str[4] = '0' + (int)  ( ( (ADDRA  >> 6) * 0.0048) * 10) % 10;
		if(str[4] > '9'){str[4] = '0';}
		
		str[2] = '0' + (int) ( ( (ADDRA  >> 6) * 0.0048) *10 ) / 10; 
		if(str[2] > '9'){str[2] = '0';}
	
}


//時間計算関数
void math_tokei(void)
{
	//時計用 24H	
		sta[0] = '0' + (hou / 10);
		sta[1] = '0' + (hou % 10);
		
		sta[3] = '0' + (min / 10);
		sta[4] = '0' + (min % 10);
		
		sta[6] = '0' + (sec / 10);
		sta[7] = '0' + (sec % 10);
}


//デューティ比
void ondo_30(void)
{
	    GRB2 = 998;
	    sndData('h');
	   	sndData('o');
	   	sndData('t'); 
	  	sndData('¥r');
       	sndData('¥n');
			
			
		str[11] = 'F';
		str[12] = 'U';
		str[13] = 'L';
		str[14] = 'L';
		
		sta[11] ='ｱ';
		sta[12] ='ﾂ';
		sta[13] ='ｲ';
		sta[14] =' ';
		
}
void ondo_28_30(void)
{
	    GRB2 = 499;
		sndData('l');
	   	sndData('h');
	   	sndData('o');
		sndData('t');
	  	sndData('¥r');
       	sndData('¥n');
			
		str[11] ='H';
		str[12] ='A';
		str[13] ='L';
		str[14] ='F';
		
		sta[11] ='ｿ';
		sta[12] ='ﾚ';
		sta[13] ='ﾅ';
		sta[14] ='ﾘ';
}
void ondo_28u(void)
{
	    GRB2 = 0;
		sndData('c');
	   	sndData('o');
	   	sndData('o'); 
		sndData('l');			 
	  	sndData('¥r');
       	sndData('¥n');
			
			
		str[11] ='S';
		str[12] ='T';
		str[13] ='O';
		str[14] ='P';
		
		sta[11] = 'ｶ';
		sta[12] = 'ｲ';
		sta[13] = 'ﾃ';
		sta[14] = 'ｷ';
		
}


//時刻の設定
void tokei_set(void)
{
	    if(~P4DR & 0x10){	sec++; if(sec > 59)	sec = 0; }
		if(~P4DR & 0x20){   min++; if(min > 59)	min = 0; }
		if(~P4DR & 0x40){	hou++; if(hou > 23)	hou = 0; }		   
		
}


//シリアル用関数
void initSci(void){
	SCR = 0x00;   
                    // SCI TE,RE:clear CKE1,CKE0 = 0
	SMR = 0x00;     // データ長8ビット，ストップビット1ビット，ノンパリティ
	BRR = 51;       // 9600bps
	SCR |= 0x30;    // TIE,RIE=0,TE,RE = 1
	//SCR |= 0xF0;    // TIE,RIE=0,TE,RE = 1
	SSR = 0x80;     // TDRE = 1,RDRF,ORER,PER,FER:clear
}

void sndData(unsigned char data){

   while((SSR & 0x80)!=0x80);  // まだ送信データがある場合，NEWデータ転送待ち
   TDR = data;                 // newデータを送信レジスタに転送
   SSR &= ~0x80;               // 送信レジスタ データありに
}

unsigned char rcvData(void){
	
	while((SSR & 0x40)!=0x40){ //受信待ち
		if(SSR & 0x38){        //エラーチェック
			SSR &= ~0x38;      //エラーフラグ消去
		}
	}

	SSR &= ~0x40;				//受信待ち状態に設定

    return RDR;					//受信データ返却
}

//シリアル用関数　終了








/*---------------終了---------------*/