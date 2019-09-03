#include "sensor.h"

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <stdbool.h>
#include <unistd.h>

#include <driver/gpio.h>

#define INTERVAL 1000000

QueueHandle_t messageQueue;
int64_t start_time = 0;

void sensor_isr_handler(void *arg)
{
  int pin = (int)arg;
  if (gpio_get_level(pin))
  {
    start_time = esp_timer_get_time();
  }
  else
  {
    int64_t time_difference = esp_timer_get_time() - start_time;
    xQueueSendFromISR(messageQueue, &time_difference, NULL);
  }
}

void periodic_timer_callback(void *arg)
{
  int triggerPin = (int)arg;
  gpio_set_level(triggerPin, 1);

  usleep(10);

  gpio_set_level(triggerPin, 0);
}

void initialize_trigger(gpio_num_t triggerPin,
                        esp_timer_handle_t *periodic_timer)
{

  gpio_config_t t;
  t.pin_bit_mask = 1ULL << triggerPin;
  t.intr_type = GPIO_INTR_DISABLE;
  t.mode = GPIO_MODE_OUTPUT;
  t.pull_down_en = GPIO_PULLDOWN_DISABLE;
  t.pull_up_en = GPIO_PULLUP_DISABLE;
  gpio_config(&t);

  const esp_timer_create_args_t periodic_timer_args = {
      .arg = (void *)triggerPin,
      .callback = periodic_timer_callback};

  esp_timer_create(&periodic_timer_args, periodic_timer);
  esp_timer_start_periodic(*periodic_timer, INTERVAL);
}

gpio_config_t sensor_conf;

QueueHandle_t initialize_sensor(gpio_num_t pin)
{
  sensor_conf.pin_bit_mask = 1ULL << pin;
  sensor_conf.intr_type = GPIO_INTR_ANYEDGE;
  sensor_conf.mode = GPIO_MODE_INPUT;
  sensor_conf.pull_up_en = GPIO_PULLUP_ENABLE;
  sensor_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  gpio_config(&sensor_conf);

  int gpioerr = 0;
  if ((gpioerr = gpio_install_isr_service(0)) != ESP_OK)
  {
    printf("ERROR: gpio_install_isr_service returned %d\n", gpioerr);
  }
  if ((gpioerr = gpio_isr_handler_add(pin, sensor_isr_handler, (void *)pin)) !=
      ESP_OK)
  {
    printf("ERROR: gpio_isr_handler_add %d\n", gpioerr);
  }

  messageQueue = xQueueCreate(10, sizeof(int64_t));
  return messageQueue;
}
