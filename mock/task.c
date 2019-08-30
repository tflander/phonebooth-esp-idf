#include <freertos/task.h>
#include <mocktask.h>
#include <string.h>

xTaskCreate_call_value_t xTaskCreate_call_value;

bool xTaskCreate_was_called_value;

void initialize_task_mocking() {
  memset(&xTaskCreate_call_value, 0, sizeof(xTaskCreate_call_value_t));
}

xTaskCreate_call_value_t *xTaskCreate_called_with() {
  return &xTaskCreate_call_value;
}

bool xTaskCreate_was_called() { return xTaskCreate_was_called_value; }

void vTaskDelay(const TickType_t xTicksToDelay) {
  // do Nothing
}

BaseType_t xTaskCreate(TaskFunction_t pvTaskCode, const char *constpcName,
                       const uint32_t usStackDepth, void *constpvParameters,
                       UBaseType_t uxPriority,
                       TaskHandle_t *constpvCreatedTask) {
  xTaskCreate_call_value.pvTaskCode = pvTaskCode;
  xTaskCreate_call_value.constpcName = constpcName;
  xTaskCreate_call_value.usStackDepth = usStackDepth;
  xTaskCreate_call_value.constpvParameters = constpvParameters;
  xTaskCreate_call_value.uxPriority = uxPriority;
  xTaskCreate_call_value.constpvCreatedTask = constpvCreatedTask;
  return 0;
}
