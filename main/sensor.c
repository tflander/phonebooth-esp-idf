#include <stdbool.h>

#include "sensor.h"
#include <driver/gpio.h>

void sensor_isr_handler(void *arg)
{
}

bool initialize_sensor(gpio_num_t pin)
{
    gpio_config_t sensor_conf;
    sensor_conf.pin_bit_mask = 1ULL << pin;
    sensor_conf.intr_type = GPIO_INTR_NEGEDGE;
    sensor_conf.mode = GPIO_MODE_INPUT;
    sensor_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    sensor_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    gpio_config(&sensor_conf);

    gpio_isr_handler_add(pin, sensor_isr_handler, (void *)pin);

    return false;
}