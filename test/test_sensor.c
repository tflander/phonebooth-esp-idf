#include "unity_fixture.h"
#include <stdbool.h>

#include "../main/sensor.h"
#include <driver/gpio.h>
#include <mockgpio.h>
#include <mockqueue.h>
#include "esp_timer.h"

#define PIN GPIO_NUM_4

TEST_GROUP(Sensor);

TEST_SETUP(Sensor)
{
    gpio_mock_initialize();
    initialize_queue_mocking();
    initialize_sensor(PIN);
}

TEST_TEAR_DOWN(Sensor) {}

TEST(Sensor, initializeSensor_InitializesSensorPin)
{
    const gpio_config_t *g = gpio_config_called_with();
    TEST_ASSERT_NOT_NULL(g);
    TEST_ASSERT_EQUAL_INT(GPIO_INTR_NEGEDGE, g->intr_type);
    TEST_ASSERT_EQUAL_INT64(1ULL << PIN, g->pin_bit_mask);
    TEST_ASSERT_EQUAL_INT(GPIO_MODE_INPUT, g->mode);
    TEST_ASSERT_EQUAL_INT(GPIO_PULLUP_DISABLE, g->pull_up_en);
    TEST_ASSERT_EQUAL_INT(GPIO_PULLDOWN_ENABLE, g->pull_down_en);
}

TEST(Sensor, initialize_sensor_AddsISRHandler)
{
    struct gpio_handler_value_t *v = get_gpio_handler_value();
    TEST_ASSERT_EQUAL_INT(PIN, v->gpio_num);
    TEST_ASSERT_EQUAL_PTR(sensor_isr_handler, v->isr_handler);
    TEST_ASSERT_EQUAL_PTR((void *)PIN, v->args);
}

TEST(Sensor, initialize_calls_xQueueCreate)
{
    TEST_ASSERT_TRUE(xQueueCreate_was_called());
    struct xQueueCreate_value *q = xQueueCreate_called_with();
    TEST_ASSERT_EQUAL_INT(sizeof(int64_t), q->uxItemSize);
}

TEST(Sensor, handle_interrupt_returns_time_spend_high)
{
    esp_timer_get_time_will_return(100);
    set_gpio_level(1);
    sensor_isr_handler((void *)PIN);

    esp_timer_get_time_will_return(200);
    set_gpio_level(0);
    sensor_isr_handler((void *)PIN);

    int64_t time_difference = get_queue_send_value();
    TEST_ASSERT_EQUAL_INT64(100, time_difference);
}

TEST_GROUP_RUNNER(Sensor)
{
    RUN_TEST_CASE(Sensor, initializeSensor_InitializesSensorPin);
    RUN_TEST_CASE(Sensor, initialize_sensor_AddsISRHandler);
    RUN_TEST_CASE(Sensor, initialize_calls_xQueueCreate);
    RUN_TEST_CASE(Sensor, handle_interrupt_returns_time_spend_high);
}
