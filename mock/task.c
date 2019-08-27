#include <freertos/task.h>


void vTaskDelay(const TickType_t xTicksToDelay)
{
    //do Nothing
}

BaseType_t xTaskCreate(TaskFunction_t pvTaskCode, const char *constpcName, const uint32_t usStackDepth, void *constpvParameters, UBaseType_t uxPriority, TaskHandle_t *constpvCreatedTask)
{
    return 0;
}