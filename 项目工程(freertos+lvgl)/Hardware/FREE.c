#include "FREE.h"

SemaphoreHandle_t xSemaphore1;  //��ֵ�ź���
SemaphoreHandle_t xSemaphore2;  //������

TaskHandle_t xTask1Handle = NULL; //���ڼ�¼����1���
TaskHandle_t xTask2Handle = NULL; //���ڼ�¼����2���
EventGroupHandle_t xCreatedEventGroup; // ���ڼ�¼�¼�����

u8 num = 0;

////led���ԵƳ�ʼ��
//void LED_Init(void) 
//	{
//    GPIO_InitTypeDef GPIO_InitStructure;  // GPIO��ʼ���ṹ��
//    
//    // ʹ��GPIOCʱ�ӣ�APB2���ߣ�
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

//    // ����PC13Ϊ�������
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;           // ѡ��PC13����
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    // �������ģʽ
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;    // ����ٶ�2MHz���ʺ�LED���ƣ�
//    
//    // ��ʼ��GPIO
//    GPIO_Init(GPIOC, &GPIO_InitStructure);

//    // ��ʼ״̬��Ϩ��LED������ߵ�ƽ��
//    GPIO_SetBits(GPIOC, GPIO_Pin_13);
//}


/***************************************************************������(BEGIN)********************************************************/

//����1����
void vTask1Code( void * pvParameters )
{
	
	printf("task1 creating\r\n");
	
    for( ;; )
    {
		num++;
		
		
		// �����ź���  P����    portMAX_DELAY û�г�ʱʱ��
		//xSemaphoreTake(xSemaphore1, portMAX_DELAY);
		
		//����
		//xSemaphoreTake(xSemaphore2, portMAX_DELAY);
		
//		//�ȴ��¼�����¼�λ������������������
//		xEventGroupWaitBits(
//							xCreatedEventGroup,  /* The event group being tested. */
//							0x01,                /* The bits within the event group to wait for. */
//							pdTRUE,              /* bit0 should be cleared before returning. */
//							pdFALSE,             /* Don't wait for both bits, either bit will do. */
//							5000                 /* Wait a maximum of 5000ms for either bit to be set. */
//							);

        //printf("task1 400\r\n");
		
		//����
		//xSemaphoreGive(xSemaphore2);
		
		//��������ʱ
		//Delay_ms(1000);
		
		//������ʱ
		vTaskDelay(1000);

		
		//��null��ʾɾ���������ľ������ɾ����������,ͬ������ִ�д˺���������
		//vTaskDelete(NULL);
		
		//��������(��ͣ����)
		//vTaskSuspend(NULL);
		

    }
}


//����2����
void vTask2Code( void * pvParameters )
{
	
	printf("task2 creating\r\n");
	
    for( ;; )
    {
		
		//OLED_ShowNum(1,4,num,2); 
		//�����ٽ������ж�ϵͳ�ᱻ�رգ������޷��л�����
		//taskENTER_CRITICAL();
		
		//���������
		//vTaskSuspendAll();
		
		//����
		//xSemaphoreTake(xSemaphore2, portMAX_DELAY);
		
        //printf("task2 400\r\n");
		
		//�����¼�����¼�λ���� 
		//xEventGroupSetBits(xCreatedEventGroup, 0x01);//����bit0
		
		//����
		//xSemaphoreGive(xSemaphore2);
		
		//Delay_ms(2000);
		
		// �ͷ��ź���  V����
		//xSemaphoreGive(xSemaphore1);
		
		//�ָ�������
		//xTaskResumeAll();
		
		//�˳��ٽ���
		//taskEXIT_CRITICAL();
		
//		//������ʱ
//		vTaskDelay(500);
		
		
//		//�ָ�����
//		vTaskResume(xTask1Handle);
//		
//		//��null��ʾɾ���������ľ������ɾ����������,ͬ������ִ�д˺���������
//		vTaskDelete(NULL);
    }
}



/***************************************************************������(END)********************************************************/
