#ifndef _MOCKGPIO_H_
#define _MOCKGPIO_H_

#include <driver/gpio.h>
#include <stdbool.h>

typedef struct {
  gpio_num_t gpio_num;
  gpio_isr_t isr_handler;
  void *args;
} gpio_handler_value_t;

typedef struct {
  gpio_num_t gpio_num;
  uint32_t level;
} gpio_set_level_value_t;

void gpio_mock_initialize();


#endif