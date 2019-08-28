#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "task.h"
#include "portmacro.h"
#include "projdefs.h"
#include "esp_err.h"

#include <stdint.h>

typedef void *QueueHandle_t;

#define queueSEND_TO_BACK ((BaseType_t)0)

#define xQueueReceive(xQueue, pvBuffer, xTicksToWait) xQueueGenericReceive((xQueue), (pvBuffer), (xTicksToWait), pdFALSE)

#define xQueueSendFromISR(xQueue, pvItemToQueue, pxHigherPriorityTaskWoken) xQueueGenericSendFromISR((xQueue), (pvItemToQueue), (pxHigherPriorityTaskWoken), queueSEND_TO_BACK)

BaseType_t xQueueGenericSendFromISR(QueueHandle_t xQueue, const void *const pvItemToQueue, BaseType_t *const pxHigherPriorityTaskWoken, const BaseType_t xCopyPosition);

BaseType_t xQueueGenericReceive(QueueHandle_t xQueue, void *const pvBuffer, TickType_t xTicksToWait, const BaseType_t xJustPeek);

QueueHandle_t xQueueCreate(uint32_t uxQueueLength, uint32_t uxItemSize);

#endif