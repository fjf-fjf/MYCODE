#ifndef __FREE_H
#define __FREE_H

#include "stm32f10x.h"  
#include "Bluetooth.h"
#include "Delay.h"
#include "OLED.h"
//FREERTOS INCLUDE
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#include "queue.h"



void vTask1Code( void * pvParameters );
void vTask2Code( void * pvParameters );
void LED_Init(void) ;


#endif
