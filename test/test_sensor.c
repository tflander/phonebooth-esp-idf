#include "unity_fixture.h"
#include <stdbool.h>

#include "../main/sensor.h"
#include <driver/gpio.h>
#include <mockgpio.h>

#define PIN GPIO_NUM_4

TEST_GROUP(Sensor);

TEST_SETUP(Sensor)
{
    gpio_mock_initialize();
}

TEST_TEAR_DOWN(Sensor) {}

TEST(Sensor, initializeSensor_InitializesSensorPin)
{
    initialize_sensor(PIN);
    const gpio_config_t *g = gpio_config_called_with();
    TEST_ASSERT_NOT_NULL(g);
    TEST_ASSERT_EQUAL_INT(GPIO_INTR_NEGEDGE, g->intr_type);
    TEST_ASSERT_EQUAL_INT64(1ULL << PIN, g->pin_bit_mask);

    // TODO Pass the following assertions
    TEST_ASSERT_EQUAL_INT(GPIO_MODE_INPUT, g->mode);
    TEST_ASSERT_EQUAL_INT(GPIO_PULLUP_DISABLE, g->pull_up_en);
    TEST_ASSERT_EQUAL_INT(GPIO_PULLDOWN_ENABLE, g->pull_down_en);
}

TEST_GROUP_RUNNER(Sensor)
{
    RUN_TEST_CASE(Sensor, initializeSensor_InitializesSensorPin);
}
