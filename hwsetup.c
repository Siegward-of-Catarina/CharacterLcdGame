#include "iodefine.h"
#include "my_define.h"
/*-------------------------------------------------------------------------------
	�֐���		: set_main_clk
	���e	 	: CPU CLOCK �̏�����
	����		: ����
	�ߒl		: ����
	�X�V��		: 2017/08/16
-------------------------------------------------------------------------------*/
void set_main_clk(void){

	unsigned int i;
	// �N���b�N���� ( HOCO 50MHz���U )
	SYSTEM.PRCR.WORD   = 0xA507;	// �v���e�N�g����
	
	SYSTEM.HOCOCR2.BYTE   = 0x03;	// 50MHz��I��  03
	SYSTEM.HOCOWTCR2.BYTE = 0x03;	// 9216cyc���U�������
	SYSTEM.HOCOCR.BYTE    = 0x00;	// HOCO���U
	for( i = 0 ; i<1750 ; i++ );	// 350��s�̔��U�ҋ@����

	// ���샂�[�h/�N���b�N������/�N���b�N���I��
	SYSTEM.OPCCR.BYTE  = 0x00;		// �������샂�[�h�ɐ؂�ւ��i�������샂�[�h1A�j
	while( SYSTEM.OPCCR.BIT.OPCMTSF );	// �������������҂�
	SYSTEM.SCKCR.LONG  = 0x10821115;	// �N���b�N������ݒ�
	while( SYSTEM.SCKCR.LONG!=0x10821115 );	// �������������҂�
	SYSTEM.VRCR = 0x00;			// SCKCR3�ύX�葱��(VRCR��0x00����������)
	SYSTEM.SCKCR3.WORD = 0x0100;		// �N���b�N����HOCO
	
	SYSTEM.PRCR.WORD   = 0xA500;	// �v���e�N�g�ݒ�
}

void set_CMT0(void)
{
	SYSTEM.PRCR.WORD = 0xA502;		//���W�X�^�ݒ苖��
	SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;	//���[�W���[���X�g�b�v�̉���
	SYSTEM.PRCR.WORD = 0xA500;		//���W�X�^�ݒ� �֎~
	
	IEN( CMT0,CMI0 ) = 0;					//���荞�݋֎~
	IPR( CMT0,CMI0 ) = 1;					//���荞�݃��x���P
	
	CMT0.CMCR.BIT.CKS = 0;				//�N���b�N�ݒ�r�b�g 8����
	CMT0.CMCNT = 0;					//CMCNT�N���A
	CMT0.CMCOR = 3;					//CMCOR�Ɏ�����ݒ� 1us
	CMT0.CMCR.BIT.CMIE = 1;				//CMT0�R���y�A�}�b�`���荞�݋���
	
	IEN( CMT0, CMI0 ) = 1;				//���荞�݋���
}
void set_CMT1(void)
{
	//��ŉ������Ă���̂ŕK�v�Ȃ�
	// SYSTEM.PRCR.WORD = 0xA502;		//���W�X�^�ݒ苖��
	// SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;	//���[�W���[���X�g�b�v�̉���
	// SYSTEM.PRCR.WORD = 0xA500;		//���W�X�^�ݒ� �֎~
	
	IEN( CMT1,CMI1 ) = 0;					//���荞�݋֎~
	IPR( CMT1,CMI1 ) = 1;					//���荞�݃��x���P
	
	CMT1.CMCR.BIT.CKS = 0;				//�N���b�N�ݒ�r�b�g 8����
	CMT1.CMCNT = 0;					//CMCNT�N���A
	CMT1.CMCOR = 3124;					//CMCOR�Ɏ�����ݒ� 1ms
	CMT1.CMCR.BIT.CMIE = 1;				//CMT0�R���y�A�}�b�`���荞�݋���
	
	IEN( CMT1, CMI1 ) = 1;				//���荞�݋���
}

void set_IRQ1(void)
{
	IEN( ICU, IRQ1 ) = 0; 				//���荞�݋֎~�ɐݒ�
	IPR( ICU, IRQ1 ) = 15; 				//���荞�ݗD��x   1 ~ 15
	
	ICU.IRQFLTE0.BIT.FLTEN1 = 0; 		//�t�B���^����
	ICU.IRQFLTC0.BIT.FCLKSEL1 = 3;		//�t�B���^�ݒ� �ő� pclk / 64
	
	SW1 = 0; 						//�o�͐ݒ�
	MPC.PWPR.BIT.B0WI = 0;			//�v���e�N�g������
	MPC.PWPR.BIT.PFSWE = 1;			//PFS���W�X�^�ւ̏������݋���
	MPC.P31PFS.BIT.ISEL = 1;			//���荞�ݒ[�q�I��
	MPC.PWPR.BIT.PFSWE = 0;			//PFS���W�X�^�ւ̏������݋֎~
	MPC.PWPR.BIT.B0WI = 1;			//�v���e�N�g��������
	SW1_PMR = 1;			//�|�[�g�@�\�����Ӌ@���
	
	ICU.IRQCR[1].BIT.IRQMD = 0x03;		//���������m��
	
	IR( ICU, IRQ1 ) = 0;				//���荞�݃t���O�������Ă���
	
	ICU.IRQFLTE0.BIT.FLTEN1 = 1; 		//�t�B���^�L��
	
	IEN( ICU, IRQ1 ) = 1; 				//���荞�݂�����
}

void set_IRQ3(void)
{
	IEN( ICU, IRQ3 ) = 0; 				//���荞�݋֎~�ɐݒ�
	IPR( ICU, IRQ3 ) = 15; 				//���荞�ݗD��x   1 ~ 15
	
	ICU.IRQFLTE0.BIT.FLTEN3 = 0; 		//�t�B���^����
	ICU.IRQFLTC0.BIT.FCLKSEL3 = 3;		//�t�B���^�ݒ� �ő� pclk / 64
	
	PORT3.PDR.BIT.B3 = 0; 			//�o�͐ݒ�
	MPC.PWPR.BIT.B0WI = 0;			//�v���e�N�g������
	MPC.PWPR.BIT.PFSWE = 1;			//PFS���W�X�^�ւ̏������݋���
	MPC.P33PFS.BIT.ISEL = 1;			//���荞�ݒ[�q�I��
	MPC.PWPR.BIT.PFSWE = 0;			//PFS���W�X�^�ւ̏������݋֎~
	MPC.PWPR.BIT.B0WI = 1;			//�v���e�N�g��������
	PORT3.PMR.BIT.B3 = 1;			//�|�[�g�@�\�����Ӌ@���
	
	ICU.IRQCR[3].BIT.IRQMD = 0x03;		//���������m��
	
	IR( ICU, IRQ3 ) = 0;				//���荞�݃t���O�������Ă���
	
	ICU.IRQFLTE0.BIT.FLTEN3 = 1; 		//�t�B���^�L��
	
	IEN( ICU, IRQ3 ) = 1; 				//���荞�݂�����
}

void set_IRQ4(void)
{
	IEN( ICU, IRQ4 ) = 0; 				//���荞�݋֎~�ɐݒ�
	IPR( ICU, IRQ4 ) = 15; 				//���荞�ݗD��x   1 ~ 15
	
	ICU.IRQFLTE0.BIT.FLTEN4 = 0; 		//�t�B���^����
	ICU.IRQFLTC0.BIT.FCLKSEL4 = 3;		//�t�B���^�ݒ� �ő� pclk / 64
	
	PORT3.PDR.BIT.B4 = 0; 			//�o�͐ݒ�
	MPC.PWPR.BIT.B0WI = 0;			//�v���e�N�g������
	MPC.PWPR.BIT.PFSWE = 1;			//PFS���W�X�^�ւ̏������݋���
	MPC.P34PFS.BIT.ISEL = 1;			//���荞�ݒ[�q�I��
	MPC.PWPR.BIT.PFSWE = 0;			//PFS���W�X�^�ւ̏������݋֎~
	MPC.PWPR.BIT.B0WI = 1;			//�v���e�N�g��������
	PORT3.PMR.BIT.B4 = 1;			//�|�[�g�@�\�����Ӌ@���
	
	ICU.IRQCR[4].BIT.IRQMD = 0x03;		//���������m��
	
	IR( ICU, IRQ4 ) = 0;				//���荞�݃t���O�������Ă���
	
	ICU.IRQFLTE0.BIT.FLTEN4 = 1; 		//�t�B���^�L��
	
	IEN( ICU, IRQ4 ) = 1; 				//���荞�݂�����
}

/*-------------------------------------------------------------------------------
	�֐���		: hw_setup
	���e	 	: �n�[�h�E�F�A�Z�b�g�A�b�v�p�֐�
	����		: ����
	�ߒl		: ����
	�X�V��		: 2017/08/16
-------------------------------------------------------------------------------*/
void HardwareSetup(void){
	
	set_main_clk();// �N���b�N�ݒ�
	set_IRQ1();
	set_IRQ3();
	set_IRQ4();
	set_CMT0();
	set_CMT1();
	return;
	
}

