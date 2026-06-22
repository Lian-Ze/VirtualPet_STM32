#include "Timer.h"

volatile uint32_t SystemTick = 0;

/**
  * @brief  TIM2初始化
  * @note   定时周期：1ms
  */
void Timer_Init(void)
{
    /* 开启TIM2时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* 选择内部时钟 */
    TIM_InternalClockConfig(TIM2);

    /* 定时器配置 */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;        // 72MHz -> 1MHz
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1;         // 1000us = 1ms
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* 清除更新标志 */
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);

    /* 开启更新中断 */
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    /* NVIC配置 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    /* 启动TIM2 */
    TIM_Cmd(TIM2, ENABLE);
}

/**
  * @brief  TIM2中断函数
  */
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        SystemTick++;
    }
}
