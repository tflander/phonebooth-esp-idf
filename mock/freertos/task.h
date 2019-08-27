#ifndef _TASK_H_
#define _TASK_H_

#include <stdint.h>

#define portTICK_PERIOD_MS  1000
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 100 )

typedef uint32_t TickType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;
typedef void (*TaskFunction_t)( void* );
typedef void * 	TaskHandle_t;

void vTaskDelay(const TickType_t xTicksToDelay);

BaseType_t xTaskCreate(TaskFunction_t pvTaskCode, const char *constpcName, const uint32_t usStackDepth, void *constpvParameters, UBaseType_t uxPriority, TaskHandle_t *constpvCreatedTask);

#endif