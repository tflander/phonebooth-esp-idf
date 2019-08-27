#include <stdbool.h>

#include "sensor.h"
#include <driver/gpio.h>

bool initialize_sensor(gpio_num_t pin)
{
    gpio_config_t io_conf;
    io_conf.pin_bit_mask = 1ULL << GPIO_NUM_4;
    gpio_config(&io_conf);
    return false;
}