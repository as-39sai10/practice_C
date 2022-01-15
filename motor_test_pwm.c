//ファイル名：motor_test_pwm.c
//スイッチON時に右モータが正転する
//PWM制御

#include "iodefine.h"

#define PERIOD	0x7530			//周期T=10ms
#define DUTY_25	0x1D4C			//デューティ比25%の設定値

void INIT_PORT(void);			//ポート初期化用関数の宣言
unsigned char getSW(void);		//スイッチ読み込み関数の宣言

void main(void)
{
	INIT_PORT();				//ポートの初期化
	
	TZ0.TCR.BIT.TPSC=2;			//内部クロック:φ/4
	TZ0.TCR.BIT.CCLR=1;			//コンペアマッチでTCNT_0をクリア
	TZ.TPMR.BIT.PWMB0=1;		//PWMモード
	TZ0.GRA=PERIOD;				//周期T=10ms
	TZ0.GRB=DUTY_25;			//デューティ設定（25%）
	TZ.TOER.BIT.EB0=0;			//FTIB0端子の出力許可
	
	while(getSW()!=1);			//スイッチが押されるまで待ち
	while(1){
		TZ.TSTR.BIT.STR0=1;		//カウント開始　TCNT_0
		IO.PDR3.BYTE=0x01;		//右モータ正転
	}
}	

void INIT_PORT(void)
{
	IO.PCR6=0xff;				//ポート6を出力に設定
	IO.PCR3=0xff;				//ポート3を出力に設定
	IO.PCR7=0x00;				//ポート7を入力に設定
	IO.PDR6.BYTE=0xff;			//ポート6を'H'に設定（LEDを消灯）

//追加（ウォッチドックタイマの停止:必要）
	WDT.TCSRWD.BYTE=0x92;	
	WDT.TCSRWD.BYTE=0x92;
	
	WDT.TCSRWD.BIT.B4WI = 0;
	WDT.TCSRWD.BIT.TCSRWE=1;

	WDT.TCSRWD.BIT.B2WI=0;
	WDT.TCSRWD.BIT.WDON=0;
	
//	WDT.TMWD.BYTE=0xFF;
//	WDT.TCSRWD.BIT.B6WI = 1;
//	WDT.TCSRWD.BIT.TCWE = 1;
//	WDT.TCWD=0x00;
//追加終了		
}

unsigned char getSW(void)
{
	unsigned char flag=0;
	if(IO.PDR7.BIT.B4==0)			//スイッチを押した場合
		flag=1;
	return flag;
}


	
	
	
	
	

