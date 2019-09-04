#include "led.h"
#include "driver/gpio.h"

void initialize_led(int pinNumber) {
  gpio_config_t c;
  c.pin_bit_mask = 1ULL << pinNumber;
  c.mode = GPIO_MODE_OUTPUT;
  c.intr_type = GPIO_INTR_DISABLE;
  gpio_config(&c);
}