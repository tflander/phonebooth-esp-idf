#include <driver/gpio.h>
#include <esp_err.h>
#include <string.h>

#include "mockgpio.h"

const gpio_config_t gpio_config_call_value;

void gpio_mock_initialize()
{
  memset((void *)&gpio_config_call_value, 0, sizeof(gpio_config_t));
}
