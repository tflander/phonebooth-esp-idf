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
#include "indicator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRIGGER_PIN GPIO_NUM_4
#define ECHO_PIN GPIO_NUM_5
#define INDICATOR_PIN GPIO_NUM_12

static QueueHandle_t sensor_queue = NULL;

void booth_logic(uint64_t echotime)
{
  uint64_t dist = echotime / 58;
  printf("Distance: %llu cm\n", dist);
  if (dist < 20)
  {
    indicator_on(true);
  }
  else
  {
    indicator_on(false);
  }
}

static void phonebooth_task(void *arg)
{
  uint64_t echotime;
  for (;;)
  {
    if (xQueueReceive(sensor_queue, &echotime, portMAX_DELAY))
    {
      booth_logic(echotime);
    }
  }
}

void app_main(void)
{
  indicator_initialize(INDICATOR_PIN);
  sensor_queue = initialize_sensor(ECHO_PIN);
  xTaskCreate(phonebooth_task, "phonebooth", 2048, NULL, 10, NULL);

  esp_timer_handle_t timer;

  initialize_trigger(TRIGGER_PIN, &timer);
}
