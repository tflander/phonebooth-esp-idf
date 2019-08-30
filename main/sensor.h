#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include <driver/gpio.h>
#include <esp_timer.h>
#include <stdbool.h>

void initialize_trigger(gpio_num_t triggerPin,
                        esp_timer_handle_t *periodic_timer);

QueueHandle_t initialize_sensor(gpio_num_t pin);

void sensor_isr_handler(void *arg);

void periodic_timer_callback(void *arg);

#endif