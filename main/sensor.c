#include <stdbool.h>

#include "sensor.h"
#include "esp_timer.h"
#include <driver/gpio.h>

#include "freertos/queue.h"

QueueHandle_t messageQueue;
int64_t start_time = 0;

void sensor_isr_handler(void *arg)
{
    int pin = (int)arg;
    if (gpio_get_level(pin))
    {
        start_time = esp_timer_get_time();
    }
    else
    {
        int64_t time_difference = esp_timer_get_time() - start_time;
        xQueueSendFromISR(messageQueue, &time_difference, NULL);
    }
}

void periodic_timer_callback(void *arg)
{
    int triggerPin = (int)arg;
    gpio_set_level(triggerPin, 1);
    // int64_t time_since_boot = esp_timer_get_time();
    // ESP_LOGI(TAG, "Periodic timer called, time since boot: %lld us", time_since_boot);
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

    xQueueCreate(10, sizeof(int64_t));

    return false;
}