#ifdef STM32F407VG

#include "config_can.h"

#define USE_INTERRUPT_CAN_RX
//#define USE_INTERRUPT_CAN_TX

void Init_CAN(int can_num,uint8_t CAN_Mode,GPIO_TypeDef *tx_port,uint16_t tx_pin,GPIO_TypeDef *rx_port,uint16_t rx_pin){

	/* Define InitTypeDef ---------------------------------------------------*/
	CAN_InitTypeDef 		CAN_InitStructure;

	/* initialize InitTypeDef -----------------------------------------------*/
	CAN_StructInit(&CAN_InitStructure);
	/* Supply clock source --------------------------------------------------*/
	if(can_num == 1){
		CAN_DeInit(CAN1);
		RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN1, ENABLE);
	}else if(can_num == 2){
		CAN_DeInit(CAN2);
		RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN2, ENABLE);
	}
	/* Define gpio_config ---------------------------------------------------*/
	
	Init_port(GPIO_Mode_AF,tx_port,tx_pin,GPIO_PuPd_UP,GPIO_OType_PP);
	Init_port(GPIO_Mode_AF,rx_port,rx_pin,GPIO_PuPd_UP,GPIO_OType_PP);

	if(can_num == 1){
		GPIO_PinAFConfig(tx_port, Pin_select_source(tx_pin), GPIO_AF_CAN1);//Tx
		GPIO_PinAFConfig(rx_port, Pin_select_source(rx_pin), GPIO_AF_CAN1);//Rx
	}else if(can_num == 2){
		GPIO_PinAFConfig(tx_port, Pin_select_source(tx_pin), GPIO_AF_CAN2);//Tx
		GPIO_PinAFConfig(rx_port, Pin_select_source(rx_pin), GPIO_AF_CAN2);//Rx
	}
	/* Set up CAN function -------------------------------------------------*/
	/* �^�C���g���K�ʐM���[�h�̗L�����E��������ݒ肷�� */
	CAN_InitStructure.CAN_TTCM 		= ENABLE;

	/* �����o�X�I�t�Ǘ�(Automatic Bus-Off Management)�̗L�����E��������ݒ肷�� */
	CAN_InitStructure.CAN_ABOM 		= DISABLE;

	/* �����ċN�����[�h�̗L�����E��������ݒ肷��  */
	CAN_InitStructure.CAN_AWUM 		= DISABLE;

	/* �����đ��M�֎~��L�����E���������� DISABLE: �����đ��M�֎~�𖳌���(�܂�đ��M�͗L��) ENABLE: �����đ��M�֎~�B����ɑ��M����Ȃ��Ă����M��1�񂾂��s���� */
	CAN_InitStructure.CAN_NART 		= DISABLE;

	/* ��MFIFO���b�N���[�h�̗L�����E��������ݒ肷�� */
	CAN_InitStructure.CAN_RFLM 		= DISABLE;

	/* ���MFIFO�̑��M�������w�肷��BDISABLE:���b�Z�[�WID�ő��M���������肳���  ENABLE:�\�t�g�E�F�A�ő��M�v�����������ꂽ���Ԃő��M����� */
	CAN_InitStructure.CAN_TXFP 		= DISABLE;

	/* CAN��Mode��ݒ肷�� */
//	CAN_InitStructure.CAN_Mode 		= CAN_Mode_Normal;
	CAN_InitStructure.CAN_Mode 		= CAN_Mode;

	/* �ē����W�����v��(CAN�n�[�h�E�F�A���ē������s���ۂ̃r�b�g��)�����ԒP�ʂ̐��Őݒ肷�� */
	CAN_InitStructure.CAN_SJW 		= CAN_SJW_1tq;

	/* CAN�r�b�g�^�C�~���O���W�X�^(CAN_BTR)��TS1[3:0]��ݒ肷��B */
	CAN_InitStructure.CAN_BS1 		= CAN_BS1_6tq;

	/* CAN�r�b�g�^�C�~���O���W�X�^(CAN_BTR)��TS2[2:0]��ݒ肷�� */
	CAN_InitStructure.CAN_BS2 		= CAN_BS2_7tq;

	/* �{�[���[�g�v���X�P�[���ݒ肷�� 1�`1024 APB1=42MHz*/
	CAN_InitStructure.CAN_Prescaler	= 3;
	//1Mbps

	if(can_num == 1){
		CAN_Init(CAN1, &CAN_InitStructure);
	}else if(can_num == 2){
		CAN_Init(CAN2, &CAN_InitStructure);
	}



#ifdef USE_INTERRUPT_CAN_RX
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	if(can_num == 1){
		NVIC_Configuration(CAN1_RX0_IRQn);
		CAN_ITConfig(CAN1, CAN_IT_FMP0,ENABLE);//message pending Interrupt
		/*
		CAN_ITConfig(CAN1, CAN_IT_EWG, ENABLE);//Error passive Interrupt
		CAN_ITConfig(CAN1, CAN_IT_EPV, ENABLE);//Error passive Interrupt
		CAN_ITConfig(CAN1, CAN_IT_BOF, ENABLE);//Bus-off Interrupt
		CAN_ITConfig(CAN1, CAN_IT_LEC, ENABLE);//tLast error code Interrupt
		CAN_ITConfig(CAN1, CAN_IT_ERR, ENABLE);//Error Interrupt
		*/
	}else if(can_num == 2){
		NVIC_Configuration(CAN2_RX0_IRQn);
		CAN_ITConfig(CAN2, CAN_IT_FMP0,ENABLE);//message pending Interrupt
		/*
		CAN_ITConfig(CAN2, CAN_IT_EWG, ENABLE);//Error passive Interrupt
		CAN_ITConfig(CAN2, CAN_IT_EPV, ENABLE);//Error passive Interrupt
		CAN_ITConfig(CAN2, CAN_IT_BOF, ENABLE);//Bus-off Interrupt
		CAN_ITConfig(CAN2, CAN_IT_LEC, ENABLE);//tLast error code Interrupt
		CAN_ITConfig(CAN2, CAN_IT_ERR, ENABLE);//Error Interrupt
		*/
	}
#endif

#ifdef USE_INTERRUPT_CAN_TX
	if(can_num == 1){
		CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);//Transmit mailbox empty Interrupt
	}else if(can_num == 2){
		CAN_ITConfig(CAN2, CAN_IT_TME, ENABLE);//Transmit mailbox empty Interrupt
	}
#endif

}



void Init_CANfilter(int filter_num,can_filter_mode_t mode
					,short stid0,can_flame_t rtr0,short stid1,can_flame_t rtr1
					,short stid2,can_flame_t rtr2,short stid3,can_flame_t rtr3){
	/* Define variable ------------------------------------------------------*/
	CAN_FilterInitTypeDef	CAN_FilterInitStructure;
	short i=0;
	/* Set up CAN Filter function -------------------------------------------------*/

#ifndef FIRST_CONTACT
#define FIRST_CONTACT
	for(i=0;i<14;i++){
		CAN_FilterInitStructure.CAN_FilterNumber = i;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
		CAN_FilterInitStructure.CAN_FilterActivation = DISABLE;
		CAN_FilterInit(&CAN_FilterInitStructure);
	}
#endif

	CAN_FilterInitStructure.CAN_FilterNumber = filter_num;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;


	if(mode == CAN_MASK){/* �t�B���^�[���[�h�ݒ� */
		CAN_FilterInitStructure.CAN_FilterMode	= CAN_FilterMode_IdMask;
	}else if(mode == CAN_LIST){
		CAN_FilterInitStructure.CAN_FilterMode	= CAN_FilterMode_IdList;
	}
	CAN_FilterInitStructure.CAN_FilterScale		 = CAN_FilterScale_16bit;
	CAN_FilterInitStructure.CAN_FilterIdLow		 = 	(stid0 << 5) |	(rtr0 << 4);
	CAN_FilterInitStructure.CAN_FilterMaskIdLow	 = 	(stid1 << 5) |	(rtr1 << 4);
	CAN_FilterInitStructure.CAN_FilterIdHigh	 = 	(stid2 << 5) |	(rtr2 << 4);
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 	(stid3 << 5) |	(rtr3 << 4);
	CAN_FilterInit(&CAN_FilterInitStructure);

}
void send_can1(CanTxMsg *data){
	CAN_Transmit(CAN1, data);
	while(CANTXOK != CAN_TransmitStatus(CAN1,0));
}
#endif//STM32F407VG
