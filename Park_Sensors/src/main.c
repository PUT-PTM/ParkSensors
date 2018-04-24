#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int i=0, j=0, lewa=0, srodek=0, prawa=0;
int TIM3_CNT;
float Distance_1, Distance_2, Distance_3;

///////////////////////// CZUJNIK I /////////////////////////////////
void ECHO1_IRQ_config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);

	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line4;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}
void hcsr04_1_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_InitTypeDef  Trigger1;
    Trigger1.GPIO_Pin = GPIO_Pin_5;
    Trigger1.GPIO_Mode = GPIO_Mode_OUT;
    Trigger1.GPIO_OType = GPIO_OType_PP;
    Trigger1.GPIO_Speed = GPIO_Speed_100MHz;
    Trigger1.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &Trigger1);

    GPIO_InitTypeDef  Echo1;
    Echo1.GPIO_Pin = GPIO_Pin_4;
    Echo1.GPIO_Mode = GPIO_Mode_IN;
    Echo1.GPIO_OType = GPIO_OType_PP;
    Echo1.GPIO_Speed = GPIO_Speed_100MHz;
    Echo1.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &Echo1);

    ECHO1_IRQ_config();
}
void EXTI_Line_4_Enable(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
}
void EXTI_Line_4_Disable(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
}
void EXTI4_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
    	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4))
    	{
    		TIM_Cmd(TIM3, ENABLE);
    		EXTI_ClearITPendingBit(EXTI_Line4);
    	}
    	else if (!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4))
		{
    		TIM_Cmd(TIM3, DISABLE);
			TIM3_CNT = TIM3->CNT;
			Distance_1 = TIM3_CNT*0.01724137931;
			if(TIM3_CNT > 8642)//ok 150 cm
				lewa=0;
			if(TIM3_CNT <= 8642 && TIM3_CNT > 5742) // miedzy 150 a 100 cm
				lewa=1;
			if(TIM3_CNT <= 5742 && TIM3_CNT > 2262) // miedzy 100 a 40 cm
				lewa=2;
			if(TIM3_CNT <= 2262) // ponizej 40 cm
				lewa=3;
			EXTI_Line_4_Disable();
			EXTI_ClearITPendingBit(EXTI_Line4);
		}
    }
}
///////////////////////// CZUJNIK II /////////////////////////////////
void ECHO2_IRQ_config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);

	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line2;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}
void hcsr04_2_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef  Trigger2;
    Trigger2.GPIO_Pin = GPIO_Pin_3;
    Trigger2.GPIO_Mode = GPIO_Mode_OUT;
    Trigger2.GPIO_OType = GPIO_OType_PP;
    Trigger2.GPIO_Speed = GPIO_Speed_100MHz;
    Trigger2.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &Trigger2);

    GPIO_InitTypeDef  Echo2;
    Echo2.GPIO_Pin = GPIO_Pin_2;
    Echo2.GPIO_Mode = GPIO_Mode_IN;
    Echo2.GPIO_OType = GPIO_OType_PP;
    Echo2.GPIO_Speed = GPIO_Speed_100MHz;
    Echo2.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &Echo2);

    ECHO2_IRQ_config();
}
void EXTI_Line_2_Enable(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);
}
void EXTI_Line_2_Disable(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);
}
void EXTI2_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
    	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))
    	{
    		TIM_Cmd(TIM3, ENABLE);
    		EXTI_ClearITPendingBit(EXTI_Line2);
    	}
    	else if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))
		{
    		TIM_Cmd(TIM3, DISABLE);
			TIM3_CNT = TIM3->CNT;
			Distance_3 = TIM3_CNT*0.01724137931;
			if(TIM3_CNT > 8642)
				srodek=0;
			if(TIM3_CNT <= 8642 && TIM3_CNT > 5742)
				srodek=1;
			if(TIM3_CNT <= 5742 && TIM3_CNT > 2262)
				srodek=2;
			if(TIM3_CNT <= 2262)
				srodek=3;
			EXTI_Line_2_Disable();
			EXTI_ClearITPendingBit(EXTI_Line2);
		}
    }
}
///////////////////////// CZUJNIK III /////////////////////////////////
void ECHO3_IRQ_config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);

	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}
void hcsr04_3_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_InitTypeDef  Trigger3;
    Trigger3.GPIO_Pin = GPIO_Pin_1;
    Trigger3.GPIO_Mode = GPIO_Mode_OUT;
    Trigger3.GPIO_OType = GPIO_OType_PP;
    Trigger3.GPIO_Speed = GPIO_Speed_100MHz;
    Trigger3.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &Trigger3);

    GPIO_InitTypeDef  Echo3;
    Echo3.GPIO_Pin = GPIO_Pin_0;
    Echo3.GPIO_Mode = GPIO_Mode_IN;
    Echo3.GPIO_OType = GPIO_OType_PP;
    Echo3.GPIO_Speed = GPIO_Speed_100MHz;
    Echo3.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &Echo3);

    ECHO3_IRQ_config();
}
void EXTI_Line_0_Enable(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);
}
void EXTI_Line_0_Disable(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);
}
void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
    	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0))
    	{
    		TIM_Cmd(TIM3, ENABLE);
    		EXTI_ClearITPendingBit(EXTI_Line0);
    	}
    	else if (!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0))
		{
    		TIM_Cmd(TIM3, DISABLE);
			TIM3_CNT = TIM3->CNT;
			Distance_3 = TIM3_CNT*0.01724137931;
			if(TIM3_CNT > 8642)
				prawa=0;
			if(TIM3_CNT <= 8642 && TIM3_CNT > 5742)
				prawa=1;
			if(TIM3_CNT <= 5742 && TIM3_CNT > 2262)
				prawa=2;
			if(TIM3_CNT <= 2262)
				prawa=3;
			EXTI_Line_0_Disable();
			EXTI_ClearITPendingBit(EXTI_Line0);
		}
    }
}
///////////////////////// SEKCJA TIMERÓW /////////////////////////////////
void tim2_init(void)
{
	//odpowiada za wysylanie sygnalow TRIGGER
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 2100;
	TIM_TimeBaseStructure.TIM_Prescaler = 4000;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM2, ENABLE);
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_SetCounter(TIM3,0);
		TIM_SetCounter(TIM7,0);
		i++;
		if(i>2)
			i=0;
		switch(i)
		{
		case 0:{
			EXTI_Line_4_Enable();
			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
			GPIO_SetBits(GPIOE,GPIO_Pin_5);
			TIM_Cmd(TIM7,ENABLE);
			};break;
		case 1:{
			EXTI_Line_2_Enable();
			GPIO_ResetBits(GPIOA,GPIO_Pin_3);
			GPIO_SetBits(GPIOA,GPIO_Pin_3);
			TIM_Cmd(TIM7,ENABLE);
			};break;
		case 2:{
			EXTI_Line_0_Enable();
			GPIO_ResetBits(GPIOE,GPIO_Pin_1);
			GPIO_SetBits(GPIOE,GPIO_Pin_1);
			TIM_Cmd(TIM7,ENABLE);
			};break;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
void tim3_init(void)
{
	/*mierzy czas trwania sygnalow echo*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/*f inc = 1 000 000 (T=1us)*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 99999;
	TIM_TimeBaseStructure.TIM_Prescaler = 83;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM3, DISABLE);
}
void tim7_init(void)
{
	/*czas trwania sygnalu trig*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	//f reload = 50 000Hz => T = 20us
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 839;
	TIM_TimeBaseStructure.TIM_Prescaler = 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM7, DISABLE);
}
void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
		switch(i)
		{
		case 0:{
			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
			TIM_Cmd(TIM7, DISABLE);
		};break;
		case 1:{
			GPIO_ResetBits(GPIOA,GPIO_Pin_3);
			TIM_Cmd(TIM7, DISABLE);
		};break;
		case 2:{
			GPIO_ResetBits(GPIOE,GPIO_Pin_1);
			TIM_Cmd(TIM7, DISABLE);
		};break;
		}
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	}
}
///////////////////////// WYSWIETLACZ /////////////////////////////////
void display_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
void tim5_init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 400-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 525-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM5, ENABLE);
}
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		switch(j)
		{
		case 0:{ GPIO_SetBits(GPIOD,GPIO_Pin_4);GPIO_ResetBits(GPIOD, GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_3);
			switch(lewa)
			{
			case 0:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);};break;
			case 1:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);GPIO_ResetBits(GPIOD,GPIO_Pin_5);GPIO_ResetBits(GPIOA, GPIO_Pin_7);};break;
			case 2:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);GPIO_ResetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_7);GPIO_ResetBits(GPIOA, GPIO_Pin_7);};break;
			case 3:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);GPIO_ResetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); GPIO_SetBits(GPIOA, GPIO_Pin_7);};break;
			}
		j++;};break;
		case 1:{ GPIO_SetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_3);GPIO_ResetBits(GPIOD, GPIO_Pin_1|GPIO_Pin_4);
			switch(srodek)
			{
			case 0:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);};break;
			case 1:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);GPIO_ResetBits(GPIOD,GPIO_Pin_5);GPIO_ResetBits(GPIOA, GPIO_Pin_7);};break;
			case 2:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);GPIO_ResetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_7);GPIO_ResetBits(GPIOA, GPIO_Pin_7);};break;
			case 3:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);GPIO_ResetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); GPIO_SetBits(GPIOA, GPIO_Pin_7);};break;
			}
		j++;};break;
		case 2:{GPIO_SetBits(GPIOD,GPIO_Pin_1);GPIO_ResetBits(GPIOD, GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
			switch(prawa)
			{
			case 0:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);};break;
			case 1:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);GPIO_ResetBits(GPIOD,GPIO_Pin_5);GPIO_ResetBits(GPIOA, GPIO_Pin_7);};break;
			case 2:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);GPIO_ResetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_7);GPIO_ResetBits(GPIOA, GPIO_Pin_7);};break;
			case 3:{GPIO_SetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);GPIO_ResetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); GPIO_SetBits(GPIOA, GPIO_Pin_7);};break;
			}
		j++;};break;
		}
	if(j>2)
		j=0;
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}
///////////////////////// BUZZER /////////////////////////////////
void Buzz_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef  Buzz;
    Buzz.GPIO_Pin = GPIO_Pin_7;
    Buzz.GPIO_Mode = GPIO_Mode_OUT;
    Buzz.GPIO_OType = GPIO_OType_PP;
    Buzz.GPIO_Speed = GPIO_Speed_100MHz;
    Buzz.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &Buzz);
}
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	hcsr04_1_init();
	hcsr04_2_init();
	hcsr04_3_init();
	display_init();
	Buzz_init();
	tim5_init();
	tim2_init();
	tim3_init();
	tim7_init();

	for(;;);
}
