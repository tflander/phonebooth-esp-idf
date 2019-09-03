#include "indicator.h"
#include "driver/gpio.h"

gpio_num_t pin_number;

void indicator_initialize(gpio_num_t pin)
{
    gpio_config_t t;
    t.pin_bit_mask = 1ULL << pin;
    t.intr_type = GPIO_INTR_DISABLE;
    t.mode = GPIO_MODE_OUTPUT;
    gpio_config(&t);
    pin_number = pin;
}

void indicator_on(bool state)
{
    gpio_set_level(pin_number, state);
}
