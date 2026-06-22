#include "stm32f10x.h"
#include "Buzzer.h"
#include "Delay.h"

void Buzzer_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 开启GPIOA时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* PA0 推挽输出 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 默认关闭蜂鸣器（低电平有效，因此输出高电平） */
    GPIO_SetBits(GPIOA, GPIO_Pin_0);
}

void Buzzer_On(void)
{
    /* 输出低电平，蜂鸣器响 */
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

void Buzzer_Off(void)
{
    /* 输出高电平，蜂鸣器关闭 */
    GPIO_SetBits(GPIOA, GPIO_Pin_0);
}

void Buzzer_Beep(uint16_t Time)
{
    Buzzer_On();
    Delay_ms(Time);
    Buzzer_Off();
}