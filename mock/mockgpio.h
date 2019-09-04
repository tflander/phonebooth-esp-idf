#ifndef _MOCKGPIO_H_
#define _MOCKGPIO_H_

#include <driver/gpio.h>
#include <stdbool.h>
const gpio_config_t *gpio_config_called_with();

void mockgpio_initialize();

#endif