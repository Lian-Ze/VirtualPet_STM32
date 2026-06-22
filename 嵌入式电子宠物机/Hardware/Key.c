#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"

void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启GPIOA、GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                           RCC_APB2Periph_GPIOB,
                           ENABLE);

    // PB0（喂食）
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // PA4（医疗）+ PA6（玩耍）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Key_Feed(void)
{
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
    {
        Delay_ms(20);

        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0);

        Delay_ms(20);

        return 1;
    }

    return 0;
}

uint8_t Key_Play(void)
{
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)
    {
        Delay_ms(20);

        while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0);

        Delay_ms(20);

        return 1;
    }

    return 0;
}

uint8_t Key_Medical(void)
{
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0)
    {
        Delay_ms(20);

        while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0);

        Delay_ms(20);

        return 1;
    }

    return 0;
}