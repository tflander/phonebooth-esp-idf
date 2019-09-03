/* GPIO Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRIGGER_PIN GPIO_NUM_4
#define ECHO_PIN GPIO_NUM_5

static QueueHandle_t sensor_queue = NULL;

static void phonebooth_task(void *arg)
{
  uint64_t echotime;
  for (;;)
  {
    if (xQueueReceive(sensor_queue, &echotime, portMAX_DELAY))
    {
      printf("Echo time: %llu\n", echotime);
    }
  }
}

void app_main(void)
{
  sensor_queue = initialize_sensor(ECHO_PIN);
  xTaskCreate(phonebooth_task, "phonebooth", 2048, NULL, 10, NULL);

  esp_timer_handle_t timer;

  initialize_trigger(TRIGGER_PIN, &timer);
}
