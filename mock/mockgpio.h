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

const gpio_config_t *gpio_config_called_with();

const gpio_set_level_value_t *gpio_set_level_call_with_values(int index);

int gpio_set_level_call_values_length();

gpio_handler_value_t *get_gpio_handler_value();

int64_t get_queue_send_value();

void set_gpio_level(int level);

bool gpio_install_isr_service_was_called();

#endif