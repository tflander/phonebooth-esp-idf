#ifndef _MOCKTASK_H_
#define _MOCKTASK_H_

#include "freertos/task.h"
#include <stdbool.h>

typedef struct {
  TaskFunction_t pvTaskCode;
  const char *constpcName;
  uint32_t usStackDepth;
  void *constpvParameters;
  UBaseType_t uxPriority;
  TaskHandle_t *constpvCreatedTask;
} xTaskCreate_call_value_t;

void initialize_task_mocking();

xTaskCreate_call_value_t *xTaskCreate_called_with();

bool xTaskCreate_was_called();

#endif