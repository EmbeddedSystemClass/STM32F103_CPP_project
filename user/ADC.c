#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "ADC.h"

float ADC_value=0;


void ADC1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE );	  //ʹ��ADC1ͨ��ʱ��
		//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

}

void Adc1_Init(void)  
{     

  ADC_InitTypeDef  ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);   //����ADC��Ƶ����6 64M/8=8,ADC���ʱ�䲻�ܳ���14M
  
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
   ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular configuration */ 

	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_7Cycles5);

   //ADC_DMACmd(ADC1 , ENABLE);
   //ADC_ExternalTrigConvCmd(ADC1, ENABLE);
  
   ADC_Cmd(ADC1 , ENABLE);   
   ADC_ResetCalibration(ADC1);
   while(ADC_GetResetCalibrationStatus(ADC1)){};
   ADC_StartCalibration(ADC1);
   while(ADC_GetCalibrationStatus(ADC1)){};

}     

void ADCinit(void)
{
	ADC1_GPIO_Config();
	Adc1_Init();
}


uint16_t Get_Adc(void)   
{
      //ָ��ADC������ͨ��,һ������,����ʱ��                   
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);        //ʹ��ָ����ADC1���ת����������    
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
    return ADC_GetConversionValue(ADC1);           //����ADC1��ת�����
}
