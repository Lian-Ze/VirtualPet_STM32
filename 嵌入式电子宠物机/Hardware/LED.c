#include "stm32f10x.h"
#include "LED.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    LED_OFF();
}

void LED_ON(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void LED_OFF(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void LED_Toggle(void)
{
    if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == Bit_SET)
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    }
    else
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
    }
}
