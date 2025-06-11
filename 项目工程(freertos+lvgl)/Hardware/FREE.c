#include "FREE.h"

SemaphoreHandle_t xSemaphore1;  //二值信号量
SemaphoreHandle_t xSemaphore2;  //互斥锁

TaskHandle_t xTask1Handle = NULL; //用于记录任务1句柄
TaskHandle_t xTask2Handle = NULL; //用于记录任务2句柄
EventGroupHandle_t xCreatedEventGroup; // 用于记录事件组句柄

u8 num = 0;

////led测试灯初始化
//void LED_Init(void) 
//	{
//    GPIO_InitTypeDef GPIO_InitStructure;  // GPIO初始化结构体
//    
//    // 使能GPIOC时钟（APB2总线）
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

//    // 配置PC13为推挽输出
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;           // 选择PC13引脚
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    // 推挽输出模式
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;    // 输出速度2MHz（适合LED控制）
//    
//    // 初始化GPIO
//    GPIO_Init(GPIOC, &GPIO_InitStructure);

//    // 初始状态：熄灭LED（输出高电平）
//    GPIO_SetBits(GPIOC, GPIO_Pin_13);
//}


/***************************************************************任务函数(BEGIN)********************************************************/

//任务1函数
void vTask1Code( void * pvParameters )
{
	
	printf("task1 creating\r\n");
	
    for( ;; )
    {
		num++;
		
		
		// 申请信号量  P操作    portMAX_DELAY 没有超时时间
		//xSemaphoreTake(xSemaphore1, portMAX_DELAY);
		
		//上锁
		//xSemaphoreTake(xSemaphore2, portMAX_DELAY);
		
//		//等待事件组的事件位成立，不成立则阻塞
//		xEventGroupWaitBits(
//							xCreatedEventGroup,  /* The event group being tested. */
//							0x01,                /* The bits within the event group to wait for. */
//							pdTRUE,              /* bit0 should be cleared before returning. */
//							pdFALSE,             /* Don't wait for both bits, either bit will do. */
//							5000                 /* Wait a maximum of 5000ms for either bit to be set. */
//							);

        //printf("task1 400\r\n");
		
		//解锁
		//xSemaphoreGive(xSemaphore2);
		
		//非阻塞延时
		//Delay_ms(1000);
		
		//阻塞延时
		vTaskDelay(1000);

		
		//填null表示删除自身，填别的句柄可以删除其他任务,同样不会执行此函数后的语句
		//vTaskDelete(NULL);
		
		//挂起任务(暂停任务)
		//vTaskSuspend(NULL);
		

    }
}


//任务2函数
void vTask2Code( void * pvParameters )
{
	
	printf("task2 creating\r\n");
	
    for( ;; )
    {
		
		//OLED_ShowNum(1,4,num,2); 
		//进入临界区，中断系统会被关闭，导致无法切换任务
		//taskENTER_CRITICAL();
		
		//挂起调度器
		//vTaskSuspendAll();
		
		//上锁
		//xSemaphoreTake(xSemaphore2, portMAX_DELAY);
		
        //printf("task2 400\r\n");
		
		//设置事件组的事件位成立 
		//xEventGroupSetBits(xCreatedEventGroup, 0x01);//设置bit0
		
		//解锁
		//xSemaphoreGive(xSemaphore2);
		
		//Delay_ms(2000);
		
		// 释放信号量  V操作
		//xSemaphoreGive(xSemaphore1);
		
		//恢复调度器
		//xTaskResumeAll();
		
		//退出临界区
		//taskEXIT_CRITICAL();
		
//		//阻塞延时
//		vTaskDelay(500);
		
		
//		//恢复任务
//		vTaskResume(xTask1Handle);
//		
//		//填null表示删除自身，填别的句柄可以删除其他任务,同样不会执行此函数后的语句
//		vTaskDelete(NULL);
    }
}



/***************************************************************任务函数(END)********************************************************/
