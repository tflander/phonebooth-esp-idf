#ifndef _MOCKGPIO_H_
#define _MOCKGPIO_H_

#include <driver/gpio.h>

void gpio_mock_initialize();

const gpio_config_t *gpio_config_called_with();

#endif