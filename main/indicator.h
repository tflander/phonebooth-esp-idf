#ifndef _INDICATOR_H_
#define _INDICATOR_H_

#include <driver/gpio.h>
#include <stdbool.h>

void indicator_initialize(gpio_num_t pin);
void indicator_on(bool);

#endif