/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void hc_sr04_1_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_InitTypeDef  Trigger1;
    Trigger1.GPIO_Pin = GPIO_Pin_4;
    Trigger1.GPIO_Mode = GPIO_Mode_OUT;
    Trigger1.GPIO_OType = GPIO_OType_PP;
    Trigger1.GPIO_Speed = GPIO_Speed_100MHz;
    Trigger1.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &Trigger1);

    GPIO_InitTypeDef  Echo1;
    Echo1.GPIO_Pin = GPIO_Pin_5;
    Echo1.GPIO_Mode = GPIO_Mode_IN;
    Echo1.GPIO_OType = GPIO_OType_PP;
    Echo1.GPIO_Speed = GPIO_Speed_100MHz;
    Echo1.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &Echo1);
}
void hc_sr04_2_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_InitTypeDef  Trigger2;
    Trigger2.GPIO_Pin = GPIO_Pin_2;
    Trigger2.GPIO_Mode = GPIO_Mode_OUT;
    Trigger2.GPIO_OType = GPIO_OType_PP;
    Trigger2.GPIO_Speed = GPIO_Speed_100MHz;
    Trigger2.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &Trigger2);

    GPIO_InitTypeDef  Echo2;
    Echo2.GPIO_Pin = GPIO_Pin_3;
    Echo2.GPIO_Mode = GPIO_Mode_IN;
    Echo2.GPIO_OType = GPIO_OType_PP;
    Echo2.GPIO_Speed = GPIO_Speed_100MHz;
    Echo2.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &Echo2);
}
void hc_sr04_3_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_InitTypeDef  Trigger3;
    Trigger3.GPIO_Pin = GPIO_Pin_0;
    Trigger3.GPIO_Mode = GPIO_Mode_OUT;
    Trigger3.GPIO_OType = GPIO_OType_PP;
    Trigger3.GPIO_Speed = GPIO_Speed_100MHz;
    Trigger3.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &Trigger3);

    GPIO_InitTypeDef  Echo3;
    Echo3.GPIO_Pin = GPIO_Pin_1;
    Echo3.GPIO_Mode = GPIO_Mode_IN;
    Echo3.GPIO_OType = GPIO_OType_PP;
    Echo3.GPIO_Speed = GPIO_Speed_100MHz;
    Echo3.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &Echo3);
}
void tim2_init(void)
{
	//timer wykorzystywany do odliczania czasu trwania sygnalow ECHO
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef Timer2;
	/* czestotliwosc przeladowania nas nie interesuje */
	Timer2.TIM_Period =999999;
	Timer2.TIM_Prescaler = 83;
	Timer2.TIM_ClockDivision = TIM_CKD_DIV1;
	Timer2.TIM_CounterMode =  TIM_CounterMode_Up;
	Timer2.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &Timer2);
}
void tim3_init(void)
{
	//wykorzystywany do generowania opoznien
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef Timer3;
	 /* Przeladowanie nastepuje co 10us */
	Timer3.TIM_Period =70-1;
	Timer3.TIM_Prescaler = 12-1;
	Timer3.TIM_ClockDivision = TIM_CKD_DIV1;
	Timer3.TIM_CounterMode =  TIM_CounterMode_Up;
	Timer3.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &Timer3);
}
void delay(int l)
{
	// l=1 oznacza odczekanie 10 us
    int i;
    TIM3->CNT=0;
    TIM_Cmd(TIM3, ENABLE);
    for(i=0;i<l;i++)
    {
        while(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update))
        {
            TIM_ClearFlag(TIM3, TIM_FLAG_Update);
        }
    }
    TIM_Cmd(TIM3, DISABLE);
}
int odczyt(GPIO_TypeDef* TRIG_GPIOx, uint16_t TRIG_Pin, GPIO_TypeDef* ECHO_GPIOx, uint16_t ECHO_Pin)
{
	int tajm=0, timeout=100000;
	//upewniamy sie ze timer odlicza od 0
	TIM2->CNT=0;
	//Sygnal niski na trigger
	GPIO_ResetBits(TRIG_GPIOx, TRIG_Pin);
	//Sygnal wysoki na trigger
	GPIO_SetBits(TRIG_GPIOx, TRIG_Pin);
	//Opóznienie 10 us
	delay(1);
	//Sygnal niski na trigger
	GPIO_ResetBits(TRIG_GPIOx, TRIG_Pin);
	//czekanie na pojewienie sie sygnalu Echo, w razie braku zwraca -1
	while (GPIO_ReadInputDataBit(ECHO_GPIOx, ECHO_Pin) == Bit_RESET)
	{
		if(timeout--==0)
		{
			return -1;
		}
	}
	//w tym miejscu rozpoczynamy pomiar czasu trwania sygnalu echo
	TIM_Cmd(TIM2, ENABLE);
	//Petla while czeka do momentu kiedy sygnal bedzie 0
	while (GPIO_ReadInputDataBit(ECHO_GPIOx, ECHO_Pin) == Bit_SET);
	TIM_Cmd(TIM2, DISABLE);
	//pobranie czasu trwania stanu wysokiego
	tajm=TIM2->CNT;
	//obliczanie odleglosci w cm
	return tajm;
}
double d1=0, d2=0, d3=0;
int t;
int main(void)
{
	hc_sr04_1_init();
	hc_sr04_2_init();
	//hc_sr04_3_init();
	tim2_init();
	tim3_init();
	for(;;)
	{
		t=odczyt(GPIOE, GPIO_Pin_4, GPIOE, GPIO_Pin_5);
		delay(100);
		d1=t*0.01724137931;
		t=odczyt(GPIOE, GPIO_Pin_2, GPIOE, GPIO_Pin_3);
		d2=t*0.01724137931;
		delay(100);
		/*t=odczyt(GPIOE, GPIO_Pin_0, GPIOE, GPIO_Pin_1);
		d3=t*0.01724137931;
		delay(1000);*/
	}
}
