#include "EXIT.h"


// TIM1 ��ʼ������������ 1ms ��ʱ�ж�
void TIM1_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // 1. ʹ�� TIM1 ʱ�ӣ�TIM1 ������ APB2 ���ߣ�
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    
    // 2. ����ʱ����Ԫ
    //    ϵͳʱ��Ϊ 72MHz��TIM1 ʱ��Ƶ�� = 72MHz
    //    Ŀ�꣺1ms �ж� �� ��ʱƵ�� = 1000Hz
    //    ��ʽ��PSC = (ʱ��Ƶ�� / ��ʱƵ��) / (ARR + 1) - 1 ���򻯼��㣩
    //    ����ֱ��ȡ��PSC = 71��ARR = 999 �� (71+1)*(999+1) = 72*1000 = 72000 �� 72MHz / 72000 = 1000Hz �� 1ms
    TIM_TimeBaseStructure.TIM_Period = 999;          // �Զ���װֵ (ARR)
    TIM_TimeBaseStructure.TIM_Prescaler = 71;        // Ԥ��Ƶ�� (PSC)
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // ʱ�ӷ�Ƶ����Ӱ�춨ʱ����Ĭ�ϣ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // �߼���ʱ�����ԣ��˴����ã���Ϊ 0��
    
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    
    // 3. ��������жϱ�־�������ʼ�������������жϣ�
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    
    // 4. ʹ�� TIM1 �����ж�
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    
    // 5. ���� NVIC �ж����ȼ�
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // ��ռ���ȼ� 2 λ����Ӧ���ȼ� 2 λ
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; // TIM1 �����ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // ��ռ���ȼ����ɰ��������
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // ��Ӧ���ȼ����ɰ��������
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    // 6. ������ʱ��
    TIM_Cmd(TIM1, ENABLE);
}



// TIM1 �����жϴ����������� startup_stm32f10x_md.s ��ע�ᣩ
void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {


				
        
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update); // ����жϱ�־
    }
}