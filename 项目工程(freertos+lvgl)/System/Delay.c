#include "Delay.h"




#if  RTOS_ISUSE_delay



/**
  * @brief  微秒延时函数
  * @param  nTime: 待延时的微秒时间
  * @retval None
  * @note   只能在FreeRTOS中实现非阻塞延时，不可以在裸机环境下使用
  */
void Delay_us(__IO uint32_t nTime)
{
	uint32_t t1,t2; //用于记录读取的SysTick的值
	
	uint32_t cnt = 0; //用于记录计数累加值
	
	//读取第1次Val值
	t1 = SysTick->VAL;
	
	//进入循环
	for(;;)
	{
		//读取第2次Val值
		t2 = SysTick->VAL;
		
		//判断t1和t2是否相等
		if(t1 != t2)
		{
			//t1 > t2
			if(t1 > t2)
				cnt += t1 - t2;
			//t1 < t2
			else
				cnt += SysTick->LOAD - t2 + t1;
			
			//判断是否已经达到目标值
			if( cnt >= nTime*72 )
				break;
			
			//如果计数值未达到目标值，再循环1次
			t1 = t2;
		}	
	}
}

/**
  * @brief  毫秒延时函数
  * @param  nTime: 待延时的毫秒时间
  * @retval None
  * @note   只能在FreeRTOS中实现非阻塞延时，不可以在裸机环境下使用
  */
void Delay_ms(__IO uint32_t nTime)
{
	while(nTime--)
	{
		Delay_us(1000);
	}
}



#else




/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
* @retval 裸机环境下用
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 裸机环境下用
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
#endif
