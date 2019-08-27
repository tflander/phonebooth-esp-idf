#include <driver/gpio.h>
#include <esp_err.h>

const gpio_config_t *gpio_config_call_value;

void gpio_mock_initialize()
{
    gpio_config_call_value = NULL;
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
    gpio_config_call_value = pGPIOConfig;
    return ESP_OK;
}

const gpio_config_t *gpio_config_called_with()
{
    return gpio_config_call_value;
}