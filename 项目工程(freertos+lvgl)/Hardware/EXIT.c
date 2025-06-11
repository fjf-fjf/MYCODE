#include "EXIT.h"


// TIM1 初始化函数：配置 1ms 定时中断
void TIM1_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // 1. 使能 TIM1 时钟（TIM1 挂载在 APB2 总线）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    
    // 2. 配置时基单元
    //    系统时钟为 72MHz，TIM1 时钟频率 = 72MHz
    //    目标：1ms 中断 → 定时频率 = 1000Hz
    //    公式：PSC = (时钟频率 / 定时频率) / (ARR + 1) - 1 （简化计算）
    //    这里直接取：PSC = 71，ARR = 999 → (71+1)*(999+1) = 72*1000 = 72000 → 72MHz / 72000 = 1000Hz → 1ms
    TIM_TimeBaseStructure.TIM_Period = 999;          // 自动重装值 (ARR)
    TIM_TimeBaseStructure.TIM_Prescaler = 71;        // 预分频器 (PSC)
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 时钟分频（不影响定时，可默认）
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // 高级定时器特性，此处无用（设为 0）
    
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    
    // 3. 清除更新中断标志（避免初始化后立即进入中断）
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    
    // 4. 使能 TIM1 更新中断
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    
    // 5. 配置 NVIC 中断优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // 抢占优先级 2 位，响应优先级 2 位
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; // TIM1 更新中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 抢占优先级（可按需调整）
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // 响应优先级（可按需调整）
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    // 6. 启动定时器
    TIM_Cmd(TIM1, ENABLE);
}



// TIM1 更新中断处理函数（需在 startup_stm32f10x_md.s 中注册）
void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {


				
        
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update); // 清除中断标志
    }
}