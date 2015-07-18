#ifdef STM32F407VG
#include "config_encoder.h"

unsigned  int	g_over_under_tim1 = 0,g_over_under_tim2 = 0,
				g_over_under_tim3 = 0,g_over_under_tim4 = 0,
				g_over_under_tim5 = 0,g_over_under_tim8 = 0,
				g_over_under_tim12 = 0;

/******************************************************************************
*	�^�C�g�� �F timer1���荞�݊֐�
*	  �֐��� �F TIM1_UP_TIM10_IRQHandler
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{�z��
*	  �쐬�� �F 2014/11/11
******************************************************************************/
void TIM1_UP_TIM10_IRQHandler(void)
{
	if( ( (TIM1 -> CR1) >> 4 ) != 0 ){
		g_over_under_tim1 --;
	}else if( ( (TIM1 -> CR1) >> 4 ) == 0 ){
		g_over_under_tim1 ++;
	}

	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}

/******************************************************************************
*	�^�C�g�� �F timer2���荞�݊֐�
*	  �֐��� �F TIM2_IRQHandler
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{�z��
*	  �쐬�� �F 2014/11/11
******************************************************************************/
void TIM2_IRQHandler(void)
{
	if( ( (TIM2 -> CR1) >> 4 ) != 0 ){
		g_over_under_tim2 --;
	}else if( ( (TIM2 -> CR1) >> 4 ) == 0 ){
		g_over_under_tim2 ++;
	}

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

/******************************************************************************
*	�^�C�g�� �F timer3���荞�݊֐�
*	  �֐��� �F TIM3_IRQHandler
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{�z��
*	  �쐬�� �F 2014/11/11
******************************************************************************/
void TIM3_IRQHandler(void)
{
	if( ( (TIM3 -> CR1) >> 4 ) != 0 ){
		g_over_under_tim3 --;
	}else if( ( (TIM3 -> CR1) >> 4 ) == 0 ){
		g_over_under_tim3 ++;
	}

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

/******************************************************************************
*	�^�C�g�� �F timer4���荞�݊֐�
*	  �֐��� �F TIM4_IRQHandler
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{�z��
*	  �쐬�� �F 2014/11/11
******************************************************************************/
void TIM4_IRQHandler(void)
{
	if( ( (TIM4 -> CR1) >> 4 ) != 0 ){
		g_over_under_tim4 --;
	}else if(( (TIM4 -> CR1) >> 4 ) == 0 ){
		g_over_under_tim4 ++;
	}

	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}

/******************************************************************************
*	�^�C�g�� �F timer5���荞�݊֐�
*	  �֐��� �F TIM5_IRQHandler
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{�z��
*	  �쐬�� �F 2014/11/11
******************************************************************************/
void TIM5_IRQHandler(void)
{
	if( ( (TIM5 -> CR1) >> 4 ) != 0 ){
		g_over_under_tim5 --;
	}else if(( (TIM5 -> CR1) >> 4 ) == 0 ){
		g_over_under_tim5 ++;
	}

	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
}

/******************************************************************************
*	�^�C�g�� �F timer8���荞�݊֐�
*	  �֐��� �F TIM8_UP_TIM13_IRQHandler
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{�z��
*	  �쐬�� �F 2014/11/11
******************************************************************************/
void TIM8_UP_TIM13_IRQHandler(void)
{
	if( ( (TIM8 -> CR1) >> 4 ) != 0 ){
		g_over_under_tim8 --;
	}else if(( (TIM8 -> CR1) >> 4 ) == 0 ){
		g_over_under_tim8 ++;
	}

	TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
}

/******************************************************************************
*	�^�C�g�� �F timer12���荞�݊֐�
*	  �֐��� �F TIM12_IRQHandler
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{�z��
*	  �쐬�� �F 2014/11/11
******************************************************************************/
void TIM8_BRK_TIM12_IRQHandler(void)
{
	if( ( (TIM12 -> CR1) >> 4 ) != 0 ){
		g_over_under_tim12 --;
	}else if(( (TIM12-> CR1) >> 4 ) == 0 ){
		g_over_under_tim12 ++;
	}

	TIM_ClearITPendingBit(TIM12, TIM_IT_Update);
}


/******************************************************************************
*	�^�C�g�� �F timer1�J�E���g�Ăяo��
*	  �֐��� �F tim1_count
*	  �߂�l �F int�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{
*	  �쐬�� �F 2014/11/11
******************************************************************************/
int tim1_count( void )
{
	return ( TIM_GetCounter(TIM1) + g_over_under_tim1 * 65536);
}

/******************************************************************************
*	�^�C�g�� �F timer2�J�E���g�Ăяo��
*	  �֐��� �F tim2_count
*	  �߂�l �F int�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{
*	  �쐬�� �F 2014/11/11
******************************************************************************/
int tim2_count( void )
{
	return ( TIM_GetCounter(TIM2) + g_over_under_tim2 * 65536 );
}

/******************************************************************************
*	�^�C�g�� �F timer3�J�E���g�Ăяo��
*	  �֐��� �F tim3_count
*	  �߂�l �F int�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{
*	  �쐬�� �F 2014/11/11
******************************************************************************/
int tim3_count( void )
{
	return ( TIM_GetCounter(TIM3) + g_over_under_tim3 * 65536 );
}

/******************************************************************************
*	�^�C�g�� �F timer4�J�E���g�Ăяo��
*	  �֐��� �F tim4_count
*	  �߂�l �F int�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{�z��
*	  �쐬�� �F 2014/11/11
******************************************************************************/
int tim4_count( void )
{
	return ( TIM_GetCounter(TIM4) + g_over_under_tim4 * 65536 );
}

/******************************************************************************
*	�^�C�g�� �F timer5�J�E���g�Ăяo��
*	  �֐��� �F tim5_count
*	  �߂�l �F int�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{�z��
*	  �쐬�� �F 2014/11/11
******************************************************************************/
int tim5_count( void )
{
	return ( TIM_GetCounter(TIM5) + g_over_under_tim5 * 65536 );
}

/******************************************************************************
*	�^�C�g�� �F timer8�J�E���g�Ăяo��
*	  �֐��� �F tim8_count
*	  �߂�l �F int�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{
*	  �쐬�� �F 2014/11/11
******************************************************************************/
int tim8_count( void )
{
	return ( TIM_GetCounter(TIM8) + g_over_under_tim8 * 65536);
}

/******************************************************************************
*	�^�C�g�� �F timer12�J�E���g�Ăяo��
*	  �֐��� �F tim12_count
*	  �߂�l �F int�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F ���{
*	  �쐬�� �F 2014/11/11
******************************************************************************/
int tim12_count( void )
{
	return ( TIM_GetCounter(TIM12) + g_over_under_tim12 * 65536);
}

/******************************************************************************
*	�^�C�g�� �F �G���R�[�_�̐ݒ�
*	  �֐��� �F Init_encoder
*	  �߂�l �F void�^
*	   ����1 �F TIM_TypeDef�^ *tim
*	   ����2 �F GPIO_TypeDef�^ *port
*	   ����3 �F uint16_t�^ pin
*	  �쐬�� �F ���{�z��
*	  �쐬�� �F 2014/11/13
******************************************************************************/
void Init_encoder(TIM_TypeDef *tim,  GPIO_TypeDef *port, uint16_t pin)
{
	unsigned short i = 0;
    //�\���̐錾
	Pin_t	pin_state;

	// Define variable ------------------------------------------------------
	uint16_t PrescalerValue = 0;

	// Define InitTypeDef
	TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;      //TIM��ݒ肷�邽�߂̍\����

	// initialize InitTypeDef
	//�N���b�N�̋��� (Supply clock source)
	RCC_PeriphClock_TIM(tim);
	
	//PORT�ɃN���b�N�̋������J�n (Define gpio_config)
	Init_port(GPIO_Mode_AF, port, pin, GPIO_PuPd_UP, GPIO_OType_PP);

	Analysis_GPIO_Pin(pin, &pin_state);
	
	for(i= 0; i < 16; i ++){
		if(pin_state.user_pin[i] == 1){
			GPIO_PinAFConfig( port, Pin_select_source(pin_state.pin_address[i]), Tim_select_af(tim) );//AF�ݒ�
		}
	}

	// Set up TIM_encoder function
	// �v���X�P�[���̒l�̐ݒ�
	PrescalerValue = (uint16_t) ((SystemCoreClock ) / 84000000) - 1;

	// �����o�̒l�̐ݒ�
	TIM_TimeBaseStructure.TIM_Period = 0xffff-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(tim, &TIM_TimeBaseStructure);

	// �v���X�P�[���̐ݒ�
	TIM_PrescalerConfig(tim, PrescalerValue, TIM_PSCReloadMode_Immediate);
	TIM_EncoderInterfaceConfig(tim, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

	//�X�V���荞�ݐݒ�
	TIM_ITConfig(tim, TIM_IT_Update, ENABLE );

	//�^�C�}�[���� (TIM enable counter)
	TIM_Cmd(tim, ENABLE);

	NVIC_Configuration(Tim_irqn_select(tim));

	Reset_encoder_over_under_flow();
}

int Select_encoder_count(TIM_TypeDef* TIMx)
{
	if(TIMx == TIM1){
		return (tim1_count());
	}else if(TIMx == TIM2){
		return (tim2_count());
	}else if(TIMx == TIM3){
		return (tim3_count());
	}else if(TIMx == TIM4){
		return (tim4_count());
	}else if(TIMx == TIM5){
		return (tim5_count());
	}else if(TIMx == TIM8){
		return (tim8_count());
	}else if(TIMx == TIM12){
		return(tim12_count());
	}else{
		return 0;
	}
}


void Reset_encoder_over_under_flow(void)
{
	g_over_under_tim1 = 0;
	g_over_under_tim2 = 0;
	g_over_under_tim3 = 0;
	g_over_under_tim4 = 0;
	g_over_under_tim5 = 0;
	g_over_under_tim8 = 0;
	g_over_under_tim12 = 0;
	TIM_SetCounter(TIM1 , 0);
	TIM_SetCounter(TIM2 , 0);
	TIM_SetCounter(TIM3 , 0);
	TIM_SetCounter(TIM4 , 0);
	TIM_SetCounter(TIM5 , 0);
	TIM_SetCounter(TIM8 , 0);
	TIM_SetCounter(TIM12 , 0);
}
#endif//STM32f407VG
