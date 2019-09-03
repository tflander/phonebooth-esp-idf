#include "unity_fixture.h"

#include "../main/indicator.h"
#include "driver/gpio.h"
#include "mockgpio.h"

#define LEDPIN 16

TEST_GROUP(Indicator);

TEST_SETUP(Indicator)
{
    gpio_mock_initialize();
}

TEST_TEAR_DOWN(Indicator) {}

TEST(Indicator, indicator_initialize_setup_gpio)
{
    indicator_initialize(LEDPIN);

    const gpio_config_t *g = gpio_config_called_with();

    TEST_ASSERT_EQUAL_INT(1ULL << LEDPIN, g->pin_bit_mask);
    TEST_ASSERT_EQUAL_INT(GPIO_MODE_OUTPUT, g->mode);
    TEST_ASSERT_EQUAL_INT(GPIO_INTR_DISABLE, g->intr_type);
}

TEST_GROUP_RUNNER(Indicator)
{
    RUN_TEST_CASE(Indicator, indicator_initialize_setup_gpio);
}