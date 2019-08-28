#include "freertos/queue.h"
#include "mockqueue.h"
#include <string.h>

int64_t queue_send_value;

BaseType_t xQueueGenericSendFromISR(QueueHandle_t xQueue, const void *const pvItemToQueue, BaseType_t *const pxHigherPriorityTaskWoken, const BaseType_t xCopyPosition)
{
    memcpy(&queue_send_value, pvItemToQueue, sizeof(int64_t));
    return 0;
}

BaseType_t xQueueGenericReceive(QueueHandle_t xQueue, void *const pvBuffer, TickType_t xTicksToWait, const BaseType_t xJustPeek)
{
    return 0;
}

QueueHandle_t xQueueCreate(uint32_t uxQueueLength, uint32_t uxItemSize)
{
    queue_send_value = 0;
    QueueHandle_t *q;
    return q;
}

int64_t get_queue_send_value()
{
    return queue_send_value;
}