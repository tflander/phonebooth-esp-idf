#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <driver/gpio.h>
#include <stdbool.h>

bool initialize_sensor(gpio_num_t pin);

#endif