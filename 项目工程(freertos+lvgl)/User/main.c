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




//�ⲿ����
extern uint8_t avoid_flag; // ���Ϲ��ܱ�־λ
extern uint8_t Auto_Line_flag; // ѭ�����ܱ�־λ


extern TaskHandle_t xTask1Handle; // ����1���
extern TaskHandle_t xTask2Handle; // ����2���
extern EventGroupHandle_t xCreatedEventGroup; // ���ڼ�¼�¼�����

extern SemaphoreHandle_t xSemaphore1;  //��ֵ�ź���
extern SemaphoreHandle_t xSemaphore2;  //������

//ȫ�ֱ���
float Distance; //�ϰ������




int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//�����ж����ȼ����飬���ȼ���ΧΪ0��15
		//LED_Init();
		//1.Ӳ����ʼ��
//		SmartCar_Init();//����ģ���ʼ��
//		HCSR04_Init();//������ģ���ʼ��
//		LineWalking_GPIO_Init(); // ����ģʽGPIO��ʼ��
//		UART2_Config(9600);//������ʼ�������������������������жϺ���
		UART1_Config(115200);//����1��ʼ�����ڵ���
//		UART3_Config(9600);//����3���ں���������ͨ��
//		UART2_SendString("AT\r\n"); //����ָ��  ��Ӧ"OK\r\n"
		printf("ret start\r\n"); //����ָ��  ��Ӧ"OK\r\n"
//		Servo_SetAngle(90);//���г��������
//		Servo_SetAngle7(90);//��������ͷ���Ҷ��
//		Servo_SetAngle8(80);//��������ͷ���¶��
		OLED_Init();

	
	
		//������ֵ�ź���
		//xSemaphore1 = xSemaphoreCreateBinary();
		//����������
		//xSemaphore2 = xSemaphoreCreateMutex();
		
		//�����±�־��
		//xCreatedEventGroup = xEventGroupCreate();
	
		//2.��������
		BaseType_t xReturned;           //���ڼ�¼����ֵ

			
		xReturned = xTaskCreate(
							vTask1Code,      //����ָ�룬ָ����ں���
							"task1 for print", //�������ƣ����ַ�������
							128,             //�����ջ��������Ϊ��λ
							NULL,            //�����������������NULL
							2,               //���ȼ��𣬲�Ҫ������Χ
							&xTask1Handle    //�����������Կ�������
							);
		
		
		xReturned = xTaskCreate(
							vTask2Code,      //����ָ�룬ָ����ں���
							"task2 for print", //�������ƣ����ַ�������
							128,             //�����ջ��������Ϊ��λ
							NULL,            //�����������������NULL
							1,               //���ȼ��𣬲�Ҫ������Χ
							&xTask2Handle    //�����������Կ�������
							);
		
		
		
		//3.����������,�ú�������Ĵ��벻�ᱻִ��
		  //vTaskStartScheduler();
		
		
		
		
		
		
 

		


	while(1)
	{
		
		


		// ����ģʽ
		 if (avoid_flag  == 1)
		 {
			
		 	auto_avoidance_mode(); 
			
		 }
		 // ѭ��ģʽ
		 else if (Auto_Line_flag  == 1)
		 {
			linewalking_task();
		 }
		
		

		
		
	}
	
	
}


