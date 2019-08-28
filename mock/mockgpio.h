#ifndef _MOCKGPIO_H_
#define _MOCKGPIO_H_

#include <driver/gpio.h>

struct gpio_handler_value_t
{
    gpio_num_t gpio_num;
    gpio_isr_t isr_handler;
    void *args;
};

void gpio_mock_initialize();

const gpio_config_t *gpio_config_called_with();

struct gpio_handler_value_t *get_gpio_handler_value();

#endif