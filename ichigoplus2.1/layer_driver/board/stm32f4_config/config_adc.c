#ifdef STM32F407VG
#include "config_adc.h"

#define		NO_CHANNEL		((uint8_t)(0xFF))

static uint16_t g_ADC1_value[8] = {0};	//�`�����l����8�łƂ肠�����ݒ�
static int g_adc_port[8] = {0};


/******************************************************************************
*	�^�C�g�� �F �w�肵���s����ADC�`�����l����I��
*	  �֐��� �F Select_ADC_channel
*	  �߂�l �F uint8_t�^ 
*	   ����1 �F GPIO_TypeDef�^ *GPIOx  GPIO�i�|�C���^�j
*	   ����2 �F uint16_t�^ pin  �s���̐ݒ�
*	  �쐬�� �F �≺���F
*	  �쐬�� �F 2014/11/13
******************************************************************************/
uint8_t Select_ADC_channel(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	uint8_t ADC_channel = NO_CHANNEL;

	if(GPIOx == GPIOA){
		if(pin == GPIO_Pin_0){
			ADC_channel = ADC_Channel_0;
		}else if(pin == GPIO_Pin_1){
			ADC_channel = ADC_Channel_1;
		}else if(pin == GPIO_Pin_2){
			ADC_channel = ADC_Channel_2;
		}else if(pin == GPIO_Pin_3){
			ADC_channel = ADC_Channel_3;
		}else if(pin == GPIO_Pin_4){
			ADC_channel = ADC_Channel_4;		
		}else if(pin == GPIO_Pin_5){
			ADC_channel = ADC_Channel_5;
		}else if(pin == GPIO_Pin_6){
			ADC_channel = ADC_Channel_6;
		}else if(pin == GPIO_Pin_7){
			ADC_channel = ADC_Channel_7;
		}
	}else if(GPIOx == GPIOB){
		if(pin == GPIO_Pin_0){
			ADC_channel = ADC_Channel_8;
		}else if(pin == GPIO_Pin_1){
			ADC_channel = ADC_Channel_9;
		}
	}else if(GPIOx == GPIOC){
		if(pin == GPIO_Pin_0){
			ADC_channel = ADC_Channel_10; 
		}else if(pin == GPIO_Pin_1){
			ADC_channel = ADC_Channel_11;
		}else if(pin == GPIO_Pin_2){
			ADC_channel = ADC_Channel_12;
		}else if(pin == GPIO_Pin_3){
			ADC_channel = ADC_Channel_13;
		}else if(pin == GPIO_Pin_4){
			ADC_channel = ADC_Channel_14;
		}else if(pin == GPIO_Pin_5){
			ADC_channel = ADC_Channel_15;
		}
	}

	return (ADC_channel);
}

/******************************************************************************
*	�^�C�g�� �F ADC1�����ݒ�
*	  �֐��� �F Init_ADC1
*	  �߂�l �F void�^ 
*	   ����1 �F GPIO_TypeDef�^ *GPIOx  GPIO�i�|�C���^�j
*	   ����2 �F uint16_t�^ pin  �s���̐ݒ�
*	  �쐬�� �F �ː��h��
*	  �쐬�� �F 2014/11/13
******************************************************************************/
void Init_ADC1(GPIO_TypeDef *GPIOx, uint16_t pin){
	unsigned short i = 0;
	static unsigned short ch = 0;
//	static uint8_t ADC_channel[16] = {NO_CHANNEL};

	//�\���̕ϐ���錾
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef       DMA_InitStructure;
//	Pin_t	pin_state;

	//GPIO�̐ݒ�
	Init_port(GPIO_Mode_AN, GPIOx, pin, GPIO_PuPd_NOPULL, GPIO_OType_PP);

	//GPIO�̃s������
//	Analysis_GPIO_Pin(pin, &pin_state);

	//ADC_VBATCmd(ENABLE);//?��������Ȃ�
	//�ϊ����ʂ�DMA�]������邲�ƂɁAADC�͎��̕ϊ����J�n����悤�ɐݒ�
//	ADC_DMARequestAfterLastTransferCmd(ADC1, DISABLE);
	//ADC1���g����悤�ɂ���
//	ADC_Cmd(ADC1, DISABLE);

	//�\���̕ϐ���������
	ADC_StructInit(&ADC_InitStructure);
	ADC_CommonStructInit(&ADC_CommonInitStructure);
	DMA_StructInit(&DMA_InitStructure);

	//���W���[���X�g�b�v��Ԃ̉���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);



/*	//���茳�̃A�h���X���Œ肵�A������ADC3ConvertedValue�ɂ��ăA�h���X���C���N�������g�A����f�[�^����2��
	DMA_InitStructure.DMA_Channel = DMA_Channel_2;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC3_DR_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 2;	//�Q�`�����l���̕ϊ����ʂ𑗂邩��f�[�^���͂Q�i�`���l���𑝂₵���炱����ς���j
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�����A�h���X���C���N�������g
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0, ENABLE);

	//GPIOC�̎w��̓��͂��A�i���O�ɐݒ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;	//PC1��PC2��ݒ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//ADC3�̊�{�ݒ�
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	//ADC3�̕ϊ����[�h�ݒ�B����2�{���X�L�����ϊ����[�h�Œ����ϊ�
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//�X�L�����ϊ����[�h��
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 2;	//���͂��Q�{�i�`���l���𑝂₵���炱����ς���j
	ADC_Init(ADC3, &ADC_InitStructure);
*/
	//DMA�ݒ�
	DMA_DeInit(DMA2_Stream0);														//DMA���Ӊ�H���W�X�^�������l�ɂ���
	DMA_InitStructure.DMA_Channel 				= DMA_Channel_0;					//�`�����l���̎w��
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (uint32_t)&ADC1->DR;				//DMAy Channelx�p���Ӊ�H�̃x�[�X�A�h���X���`����
	DMA_InitStructure.DMA_Memory0BaseAddr 		= (uint32_t)&(g_ADC1_value);		//DMAy Channelx�̃��������x�[�X�A�h���X���`����
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_PeripheralToMemory;		//�f�[�^�]������
	DMA_InitStructure.DMA_BufferSize 			= ch+1;			//�o�b�t�@�T�C�Y
	DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;		//�y���t�F�������̃A�h���X��]�����ɃC���N�������g���邩�ǂ���
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;				//���������̃A�h���X��]�����ɃC���N�������g���邩�ǂ���
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_HalfWord;	//�y���t�F�������̃f�[�^�T�C�Y
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_HalfWord;		//���������̃f�[�^�T�C�Y
	DMA_InitStructure.DMA_Mode 					= DMA_Mode_Circular;				//DMA�̓��샂�[�h���w��
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_High;				//DMA�]���̃\�t�g�E�F�A�D��x
	DMA_InitStructure.DMA_FIFOMode 				= DMA_FIFOMode_Disable;				//FIFO���[�h�܂��̓_�C���N�g���[�h���w�肳�ꂽ�X�g���[���̂��߂Ɏg�p����邩�ǂ������w�肵�܂��B
	DMA_InitStructure.DMA_FIFOThreshold 		= DMA_FIFOThreshold_HalfFull;		//FIFO�������l���x�����w�肵�܂��B
	DMA_InitStructure.DMA_MemoryBurst 			= DMA_MemoryBurst_Single;			//�������]���̂��߂̃o�[�X�g�]���̐ݒ���w�肵�܂��B
	DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;		//���ӓ]���̃o�[�X�g�]���̐ݒ���w�肵�܂��B
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);										//DMA�̐ݒ�
	DMA_Cmd(DMA2_Stream0, ENABLE);													//DMA�̗L����

	//ADC�ݒ�
	ADC_DeInit();																	//
	ADC_CommonInitStructure.ADC_Mode 			= ADC_Mode_Independent;				//�Ɨ������A�܂��̓}���`���[�h�œ��삷��悤��ADC��ݒ肵�܂��B
	ADC_CommonInitStructure.ADC_Prescaler 		= ADC_Prescaler_Div2;				//ADC�ւ̃N���b�N�̎��g����I�����܂��B
	ADC_CommonInitStructure.ADC_DMAAccessMode 	= ADC_DMAAccessMode_Disabled;		//�}���`ADC���[�h�p�̃_�C���N�g�������A�N�Z�X���[�h��ݒ肵�܂��B
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;	//2�T���v�����O�ʑ��Ԃ̒x����ݒ肵�܂��B
	ADC_CommonInit(&ADC_CommonInitStructure);										//

	ADC_InitStructure.ADC_Resolution 			= ADC_Resolution_12b;				//ADC����\�̃f���A�����[�h��ݒ�
	ADC_InitStructure.ADC_ScanConvMode 			= ENABLE;							//�X�L�����i�}���`�`�����l���j�܂��̓V���O���i1�`���l���j���[�h�Ŏ��s���邩�ǂ������w��
	ADC_InitStructure.ADC_ContinuousConvMode 	= ENABLE;							//�A���܂��̓V���O�����[�h�Ŏ��s���邩�ǂ������w��
	ADC_InitStructure.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_None;	//�O���g���K�G�b�W��I�����A����I�ȃO���[�v�̃g���K���\�ɂ���
	ADC_InitStructure.ADC_ExternalTrigConv 		= 0;								//����I�Ȋ�̕ϊ��̊J�n���g���K���邽�߂Ɏg�p�����O���C�x���g��I��
	ADC_InitStructure.ADC_DataAlign 			= ADC_DataAlign_Right;				//ADC�f�[�^�E�A���C�������g�����E�ǂ���ɂ��邩���w��
	ADC_InitStructure.ADC_NbrOfConversion 		= ch+1;								//����I�ȃ`���l���O���[�v�̃V�[�P���T�[���g�p���Ď��s����܂�ADC�ϊ��̐����w�肵�܂��B
	ADC_Init(ADC1, &ADC_InitStructure);												//

	//ADC1��DMA���g����悤�ɂ���
	ADC_DMACmd(ADC1, ENABLE);

	//ADC1�̃A�i���O���͂��`����
	//ADC_Channel_11��PA1,ADC_Channel_12��PA2�B�}�j���A��(UM1472)�̃s���z�\������Ƃ킩��
	//"ADC123_IN11"�Ƃ����\�L�́AADC1,ADC2,ADC3�Ŏg������͂�channel_11�Ɋ��蓖�Ă���A�Ƃ�������
	//�g���`���l���𑝂₷�ɂ́A�����ɒǋL����B�`���l���w��̎��̃p�����[�^�͕ϊ��V�[�P���X�̏���
/*	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 3, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 4, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 5, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 6, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 7, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 8, ADC_SampleTime_480Cycles);*/
/*	ADC_RegularChannelConfig(ADC1,Select_ADC_channel(ADCPORT0), 1, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1,Select_ADC_channel(ADCPORT1), 2, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1,Select_ADC_channel(ADCPORT2), 3, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1,Select_ADC_channel(ADCPORT3), 4, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1,Select_ADC_channel(ADCPORT4), 5, ADC_SampleTime_480Cycles);
	g_adc_port[0] = Select_ADC_channel(ADCPORT0);
	g_adc_port[1] = Select_ADC_channel(ADCPORT1);
	g_adc_port[2] = Select_ADC_channel(ADCPORT2);
	g_adc_port[3] = Select_ADC_channel(ADCPORT3);
	g_adc_port[4] = Select_ADC_channel(ADCPORT4);
*/
	ch++;
	for(i=1;i<ch;i++){
		ADC_RegularChannelConfig(ADC1,g_adc_port[i-1], i, ADC_SampleTime_480Cycles);
	}

	ADC_RegularChannelConfig(ADC1,Select_ADC_channel(GPIOx,pin), ch, ADC_SampleTime_480Cycles);
	g_adc_port[ch-1] = Select_ADC_channel(GPIOx,pin);


/*	//ADC_Channel�̑I��
	for(i = 0; i <16; i ++){
		if(pin_state.user_pin[i] == 1){
			ADC_channel[i] = Select_ADC_channel(GPIOx, pin_state.pin_address[i]);
		}
	}

	//ADC1�̃A�i���O���͂��`����
	for(i = 0; i < 16; i ++){
		if(ADC_channel[i] != NO_CHANNEL){
			ch ++;
			if(ch > pin_state.user_pin_sum){
				break;
			}else{
				ADC_RegularChannelConfig(ADC1,ADC_channel[i], ch, ADC_SampleTime_480Cycles);
			}
		}
	}
*/

	//ADC_VBATCmd(ENABLE);//?��������Ȃ�
	//�ϊ����ʂ�DMA�]������邲�ƂɁAADC�͎��̕ϊ����J�n����悤�ɐݒ�
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	//ADC1���g����悤�ɂ���
	ADC_Cmd(ADC1, ENABLE);
	//�ϊ��X�^�[�g
	ADC_SoftwareStartConv(ADC1);
}

/******************************************************************************
*	�^�C�g�� �F �w�肵���`�����l����ADC1�̒l�𓾂�
*	  �֐��� �F get_ADC1_value
*	  �߂�l �F short�^ 
*	   ����1 �F unsigned short�^ ch  �`�����l��(0~7)
*	  �쐬�� �F �ː��h��
*	  �쐬�� �F 2014/11/14
******************************************************************************/
float get_ADC1_value(GPIO_TypeDef *GPIOx, uint16_t pin){
	int ch=0;
	for(ch=0;ch<8;ch++){
		if(g_adc_port[ch] == Select_ADC_channel(GPIOx,pin)){
			return ((float)g_ADC1_value[ch]);
		}
	}
	return -1;
}



#endif//STM32F407VG
