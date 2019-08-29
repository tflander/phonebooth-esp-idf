#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <driver/gpio.h>
#include <stdbool.h>

void initialize_trigger(gpio_num_t triggerPin);

bool initialize_sensor(gpio_num_t pin);

void sensor_isr_handler(void *arg);

void periodic_timer_callback(void* arg);

#endif