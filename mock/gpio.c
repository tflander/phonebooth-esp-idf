#include <driver/gpio.h>
#include <string.h>
#include <esp_err.h>

#include "mockgpio.h"

const gpio_config_t gpio_config_call_value;

struct gpio_handler_value_t gpio_handler_value;

int gpio_level_value;

void gpio_mock_initialize()
{
    memset((void *)&gpio_config_call_value, 0, sizeof(gpio_config_t));
    memset((void *)&gpio_handler_value, 0, sizeof(struct gpio_handler_value_t));
    gpio_level_value = -1;
}

esp_err_t gpio_set_direction(gpio_num_t gpio_num, gpio_mode_t mode)
{
    return ESP_OK;
}

esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level)
{
    return ESP_OK;
}

void gpio_pad_select_gpio(uint8_t gpio_num)
{
    // Do Nothing
}

esp_err_t gpio_config(const gpio_config_t *pGPIOConfig)
{
    memcpy((void *)&gpio_config_call_value, pGPIOConfig, sizeof(gpio_config_t));
    return ESP_OK;
}

const gpio_config_t *gpio_config_called_with()
{
    return &gpio_config_call_value;
}

esp_err_t gpio_isr_handler_add(gpio_num_t gpio_num, gpio_isr_t isr_handler, void *args)
{
    gpio_handler_value.gpio_num = gpio_num;
    gpio_handler_value.isr_handler = isr_handler;
    gpio_handler_value.args = args;
    return ESP_OK;
}

struct gpio_handler_value_t *get_gpio_handler_value()
{
    return &gpio_handler_value;
}

int gpio_get_level(gpio_num_t gpio_num)
{
    return gpio_level_value;
}

void set_gpio_level(int level)
{
    gpio_level_value = level;
}

esp_err_t gpio_set_intr_type(gpio_num_t gpio_num, gpio_int_type_t intr_type)
{
    return ESP_OK;
}

esp_err_t gpio_install_isr_service(int intr_alloc_flags)
{
    return ESP_OK;
}
