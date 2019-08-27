#include <stdbool.h>

#include "sensor.h"
#include <driver/gpio.h>

static gpio_config_t sensor_conf;

bool initialize_sensor(gpio_num_t pin)
{
    sensor_conf.pin_bit_mask = 1ULL << pin;
    sensor_conf.intr_type = GPIO_INTR_NEGEDGE;
    gpio_config(&sensor_conf);
    return false;
}