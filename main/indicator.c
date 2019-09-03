#include "indicator.h"
#include "driver/gpio.h"

void indicator_initialize(gpio_num_t pin)
{
    gpio_config_t t;
    t.pin_bit_mask = 1ULL << pin;
    t.intr_type = GPIO_INTR_DISABLE;
    t.mode = GPIO_MODE_OUTPUT;
    gpio_config(&t);
}

void indicator_on(bool state)
{
    // Do the thing
}
