#include "main.hpp"


void RCC_Configuration(void)
{
    RCC_DeInit();//
 
    RCC_HSICmd(ENABLE);//ʹ��HSI  
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);//�ȴ�HSIʹ�����
 
    RCC_HCLKConfig(RCC_SYSCLK_Div1);   
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    
    //���� PLL ʱ��Դ�ͱ�Ƶϵ��
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);//ʹ�ܻ���ʧ�� PLL,�����������ȡ:ENABLE ���� DISABLE 
    RCC_PLLCmd(ENABLE);
    //�ȴ�ָ���� RCC��־���óɹ����ȴ�PLL��ʼ���ɹ�
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
 
    //����ϵͳʱ��(SYSCLK) ����PLLΪϵͳʱ��Դ
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//ѡ����Ҫ��ʱ��Դ 
    //  0x00:HSI ��Ϊʱ��Դ
    //  0x04:HSE ��Ϊʱ��Դ
    //  0x08:PLL ��Ϊʱ��Դ
    while(RCC_GetSYSCLKSource() != 0x08);//??????????????,RCC_SYSCLKSource_PLL 
}


RCC_ClocksTypeDef SYSclock;

void BufProcess(uint8_t *__BUF);
int16_t PitchPWMValue=1500,YawPWMValue=1500;
uint8_t LED_State = 0;


int main(int argc, char *argv[])
{
	
	char t[]="is ok\r\n";
	RCC_Configuration();
	MotorDriverGPIO_Init();

	TIM4_init();
	USART_Config();
		
	RCC_GetClocksFreq(&SYSclock);

	GUA_Timer1_PWM_Init(20000);	
	GUA_Timer1_PWM_Status(GUA_TIMER1_PWM_STATUS_ON);   	
	
	while(1)
	{
			
		//Usart_SendString(DEBUG_USARTx,t);
		
		/*If receive Data need change data*/
		if(finishFlah==1)
		{
			finishFlah = 0;
			BufProcess(USART_RX_BUF);
			Usart_SendString(DEBUG_USARTx,t);
		}
		
		/*************************************************/
		/*Pitch Roll Yaw Control*/
		GUA_Timer1_PWM_SetDutyCycle(PitchPWMValue,PitchCH);
		GUA_Timer1_PWM_SetDutyCycle(YawPWMValue,YawCH);
		/*Control LED */
		if(LED_State==1)
		{
			TurnONLED();
		}
		else
		{
			TurnOFFLED();
		}		

		
		
	}
}

void BufProcess(uint8_t *__BUF)
{
		/*Pitch Roll Yaw Control*/
		PitchPWMValue = 	(__BUF[3]<<8) 	+ 	__BUF[2];
		YawPWMValue 	= 	(__BUF[7]<<8) 	+ 	__BUF[6];
		
		if(PitchPWMValue>=2000) PitchPWMValue= 2000;
		else if (PitchPWMValue<=1000) PitchPWMValue=1000;
		
		if(YawPWMValue>=2000) YawPWMValue= 2000;
		else if (YawPWMValue<=1000) YawPWMValue=1000;
			
		/*Control LED */
		if(__BUF[8])
				LED_State = 1; //LED ON
		else
		{
				LED_State = 0;	// LED OFF
		}
}
