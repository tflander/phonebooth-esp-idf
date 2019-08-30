#include "freertos/queue.h"
#include "mockqueue.h"
#include <string.h>

int64_t queue_send_value;
bool xQueueCreate_was_called_v;
xQueueCreate_value_t xQueueCreate_call_value;
QueueHandle_t xQueueCreate_return_value;

BaseType_t xQueueGenericSendFromISR(QueueHandle_t xQueue,
                                    const void *const pvItemToQueue,
                                    BaseType_t *const pxHigherPriorityTaskWoken,
                                    const BaseType_t xCopyPosition) {
  memcpy(&queue_send_value, pvItemToQueue, sizeof(int64_t));
  return 0;
}

BaseType_t xQueueGenericReceive(QueueHandle_t xQueue, void *const pvBuffer,
                                TickType_t xTicksToWait,
                                const BaseType_t xJustPeek) {
  return 0;
}

QueueHandle_t xQueueCreate(uint32_t uxQueueLength, uint32_t uxItemSize) {
  xQueueCreate_call_value.uxQueueLength = uxQueueLength;
  xQueueCreate_call_value.uxItemSize = uxItemSize;

  xQueueCreate_was_called_v = true;
  return xQueueCreate_return_value;
}

void initialize_queue_mocking() {
  xQueueCreate_call_value.uxItemSize = 0;
  xQueueCreate_call_value.uxQueueLength = 0;
  queue_send_value = 0;
  xQueueCreate_was_called_v = false;
  xQueueCreate_return_value = NULL;
}

xQueueCreate_value_t *xQueueCreate_called_with() {
  return &xQueueCreate_call_value;
}

bool xQueueCreate_was_called() { return xQueueCreate_was_called_v; }

void xQueueCreate_will_return(QueueHandle_t q) {
  xQueueCreate_return_value = q;
}

int64_t get_queue_send_value() { return queue_send_value; }
