#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "pwm.h"
#include "motor.h"
#include "smartcar.h"
#include "HCSR04.h"
#include "duoji.h"
#include "EXIT.h"
#include "Bluetooth.h"
#include "mode.h"
#include "linewalking.h"
#include "FREE.h"




//外部声明
extern uint8_t avoid_flag; // 避障功能标志位
extern uint8_t Auto_Line_flag; // 循迹功能标志位


extern TaskHandle_t xTask1Handle; // 任务1句柄
extern TaskHandle_t xTask2Handle; // 任务2句柄
extern EventGroupHandle_t xCreatedEventGroup; // 用于记录事件组句柄

extern SemaphoreHandle_t xSemaphore1;  //二值信号量
extern SemaphoreHandle_t xSemaphore2;  //互斥锁

//全局变量
float Distance; //障碍物距离




int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置中断优先级分组，优先级范围为0—15
		//LED_Init();
		//1.硬件初始化
//		SmartCar_Init();//动力模块初始化
//		HCSR04_Init();//超声波模块初始化
//		LineWalking_GPIO_Init(); // 线走模式GPIO初始化
//		UART2_Config(9600);//蓝牙初始化用于连接蓝牙，其中已有中断函数
		UART1_Config(115200);//串口1初始化用于调试
//		UART3_Config(9600);//串口3用于和语音助手通信
//		UART2_SendString("AT\r\n"); //测试指令  响应"OK\r\n"
		printf("ret start\r\n"); //测试指令  响应"OK\r\n"
//		Servo_SetAngle(90);//居中超声波舵机
//		Servo_SetAngle7(90);//居中摄像头左右舵机
//		Servo_SetAngle8(80);//居中摄像头上下舵机
		OLED_Init();

	
	
		//创建二值信号量
		//xSemaphore1 = xSemaphoreCreateBinary();
		//创建互斥锁
		//xSemaphore2 = xSemaphoreCreateMutex();
		
		//创建事标志组
		//xCreatedEventGroup = xEventGroupCreate();
	
		//2.创建任务
		BaseType_t xReturned;           //用于记录返回值

			
		xReturned = xTaskCreate(
							vTask1Code,      //函数指针，指向入口函数
							"task1 for print", //任务名称，是字符串常量
							128,             //任务堆栈，是以字为单位
							NULL,            //任务参数，不传可以NULL
							2,               //优先级别，不要超过范围
							&xTask1Handle    //任务句柄，可以控制任务
							);
		
		
		xReturned = xTaskCreate(
							vTask2Code,      //函数指针，指向入口函数
							"task2 for print", //任务名称，是字符串常量
							128,             //任务堆栈，是以字为单位
							NULL,            //任务参数，不传可以NULL
							1,               //优先级别，不要超过范围
							&xTask2Handle    //任务句柄，可以控制任务
							);
		
		
		
		//3.启动调度器,该函数后面的代码不会被执行
		  //vTaskStartScheduler();
		
		
		
		
		
		
 

		


	while(1)
	{
		
		


		// 避障模式
		 if (avoid_flag  == 1)
		 {
			
		 	auto_avoidance_mode(); 
			
		 }
		 // 循迹模式
		 else if (Auto_Line_flag  == 1)
		 {
			linewalking_task();
		 }
		
		

		
		
	}
	
	
}


