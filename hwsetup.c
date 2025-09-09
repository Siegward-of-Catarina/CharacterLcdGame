#include "iodefine.h"
#include "my_define.h"
/*-------------------------------------------------------------------------------
	関数名		: set_main_clk
	内容	 	: CPU CLOCK の初期化
	引数		: 無し
	戻値		: 無し
	更新日		: 2017/08/16
-------------------------------------------------------------------------------*/
void set_main_clk(void){

	unsigned int i;
	// クロック発生 ( HOCO 50MHz発振 )
	SYSTEM.PRCR.WORD   = 0xA507;	// プロテクト解除
	
	SYSTEM.HOCOCR2.BYTE   = 0x03;	// 50MHzを選択  03
	SYSTEM.HOCOWTCR2.BYTE = 0x03;	// 9216cyc発振安定期間
	SYSTEM.HOCOCR.BYTE    = 0x00;	// HOCO発振
	for( i = 0 ; i<1750 ; i++ );	// 350μsの発振待機時間

	// 動作モード/クロック分周比/クロック源選択
	SYSTEM.OPCCR.BYTE  = 0x00;		// 高速動作モードに切り替え（中速動作モード1A）
	while( SYSTEM.OPCCR.BIT.OPCMTSF );	// 書き換え完了待ち
	SYSTEM.SCKCR.LONG  = 0x10821115;	// クロック分周比設定
	while( SYSTEM.SCKCR.LONG!=0x10821115 );	// 書き換え完了待ち
	SYSTEM.VRCR = 0x00;			// SCKCR3変更手続き(VRCRに0x00を書き込む)
	SYSTEM.SCKCR3.WORD = 0x0100;		// クロック源をHOCO
	
	SYSTEM.PRCR.WORD   = 0xA500;	// プロテクト設定
}

void set_CMT0(void)
{
	SYSTEM.PRCR.WORD = 0xA502;		//レジスタ設定許可
	SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;	//モージュールストップの解除
	SYSTEM.PRCR.WORD = 0xA500;		//レジスタ設定 禁止
	
	IEN( CMT0,CMI0 ) = 0;					//割り込み禁止
	IPR( CMT0,CMI0 ) = 1;					//割り込みレベル１
	
	CMT0.CMCR.BIT.CKS = 0;				//クロック設定ビット 8周期
	CMT0.CMCNT = 0;					//CMCNTクリア
	CMT0.CMCOR = 3;					//CMCORに周期を設定 1us
	CMT0.CMCR.BIT.CMIE = 1;				//CMT0コンペアマッチ割り込み許可
	
	IEN( CMT0, CMI0 ) = 1;				//割り込み許可
}
void set_CMT1(void)
{
	//上で解除しているので必要ない
	// SYSTEM.PRCR.WORD = 0xA502;		//レジスタ設定許可
	// SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;	//モージュールストップの解除
	// SYSTEM.PRCR.WORD = 0xA500;		//レジスタ設定 禁止
	
	IEN( CMT1,CMI1 ) = 0;					//割り込み禁止
	IPR( CMT1,CMI1 ) = 1;					//割り込みレベル１
	
	CMT1.CMCR.BIT.CKS = 0;				//クロック設定ビット 8周期
	CMT1.CMCNT = 0;					//CMCNTクリア
	CMT1.CMCOR = 3124;					//CMCORに周期を設定 1ms
	CMT1.CMCR.BIT.CMIE = 1;				//CMT0コンペアマッチ割り込み許可
	
	IEN( CMT1, CMI1 ) = 1;				//割り込み許可
}

void set_IRQ1(void)
{
	IEN( ICU, IRQ1 ) = 0; 				//割り込み禁止に設定
	IPR( ICU, IRQ1 ) = 15; 				//割り込み優先度   1 ~ 15
	
	ICU.IRQFLTE0.BIT.FLTEN1 = 0; 		//フィルタ無効
	ICU.IRQFLTC0.BIT.FCLKSEL1 = 3;		//フィルタ設定 最大 pclk / 64
	
	SW1 = 0; 						//出力設定
	MPC.PWPR.BIT.B0WI = 0;			//プロテクトを解除
	MPC.PWPR.BIT.PFSWE = 1;			//PFSレジスタへの書き込み許可
	MPC.P31PFS.BIT.ISEL = 1;			//割り込み端子選択
	MPC.PWPR.BIT.PFSWE = 0;			//PFSレジスタへの書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;			//プロテクトをかける
	SW1_PMR = 1;			//ポート機能を周辺機器へ
	
	ICU.IRQCR[1].BIT.IRQMD = 0x03;		//両立ち検知へ
	
	IR( ICU, IRQ1 ) = 0;				//割り込みフラグを下げておく
	
	ICU.IRQFLTE0.BIT.FLTEN1 = 1; 		//フィルタ有効
	
	IEN( ICU, IRQ1 ) = 1; 				//割り込みを許可
}

void set_IRQ3(void)
{
	IEN( ICU, IRQ3 ) = 0; 				//割り込み禁止に設定
	IPR( ICU, IRQ3 ) = 15; 				//割り込み優先度   1 ~ 15
	
	ICU.IRQFLTE0.BIT.FLTEN3 = 0; 		//フィルタ無効
	ICU.IRQFLTC0.BIT.FCLKSEL3 = 3;		//フィルタ設定 最大 pclk / 64
	
	PORT3.PDR.BIT.B3 = 0; 			//出力設定
	MPC.PWPR.BIT.B0WI = 0;			//プロテクトを解除
	MPC.PWPR.BIT.PFSWE = 1;			//PFSレジスタへの書き込み許可
	MPC.P33PFS.BIT.ISEL = 1;			//割り込み端子選択
	MPC.PWPR.BIT.PFSWE = 0;			//PFSレジスタへの書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;			//プロテクトをかける
	PORT3.PMR.BIT.B3 = 1;			//ポート機能を周辺機器へ
	
	ICU.IRQCR[3].BIT.IRQMD = 0x03;		//両立ち検知へ
	
	IR( ICU, IRQ3 ) = 0;				//割り込みフラグを下げておく
	
	ICU.IRQFLTE0.BIT.FLTEN3 = 1; 		//フィルタ有効
	
	IEN( ICU, IRQ3 ) = 1; 				//割り込みを許可
}

void set_IRQ4(void)
{
	IEN( ICU, IRQ4 ) = 0; 				//割り込み禁止に設定
	IPR( ICU, IRQ4 ) = 15; 				//割り込み優先度   1 ~ 15
	
	ICU.IRQFLTE0.BIT.FLTEN4 = 0; 		//フィルタ無効
	ICU.IRQFLTC0.BIT.FCLKSEL4 = 3;		//フィルタ設定 最大 pclk / 64
	
	PORT3.PDR.BIT.B4 = 0; 			//出力設定
	MPC.PWPR.BIT.B0WI = 0;			//プロテクトを解除
	MPC.PWPR.BIT.PFSWE = 1;			//PFSレジスタへの書き込み許可
	MPC.P34PFS.BIT.ISEL = 1;			//割り込み端子選択
	MPC.PWPR.BIT.PFSWE = 0;			//PFSレジスタへの書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;			//プロテクトをかける
	PORT3.PMR.BIT.B4 = 1;			//ポート機能を周辺機器へ
	
	ICU.IRQCR[4].BIT.IRQMD = 0x03;		//両立ち検知へ
	
	IR( ICU, IRQ4 ) = 0;				//割り込みフラグを下げておく
	
	ICU.IRQFLTE0.BIT.FLTEN4 = 1; 		//フィルタ有効
	
	IEN( ICU, IRQ4 ) = 1; 				//割り込みを許可
}

/*-------------------------------------------------------------------------------
	関数名		: hw_setup
	内容	 	: ハードウェアセットアップ用関数
	引数		: 無し
	戻値		: 無し
	更新日		: 2017/08/16
-------------------------------------------------------------------------------*/
void HardwareSetup(void){
	
	set_main_clk();// クロック設定
	set_IRQ1();
	set_IRQ3();
	set_IRQ4();
	set_CMT0();
	set_CMT1();
	return;
	
}

