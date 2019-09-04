#include <driver/gpio.h>
#include <esp_err.h>
#include <string.h>

#include "mockgpio.h"

const gpio_config_t gpio_config_called_value;

esp_err_t gpio_config(const gpio_config_t *pGPIOConfig) {
  // Copy the actual value, rather than storing the pointer.
  // The pointer may point to a local variable in the calling function,
  // and the contents may be overwritten as soon as the calling function
  // exits.  Learn from our pain.
  memcpy((void *)&gpio_config_called_value, pGPIOConfig, sizeof(gpio_config_t));
  return ESP_OK;
}

const gpio_config_t *gpio_config_called_with() {
  return &gpio_config_called_value;
}

void mockgpio_initialize() {
  // Zero out the block of memory before each test case.
  memset((void *)&gpio_config_called_value, 0, sizeof(gpio_config_t));
}