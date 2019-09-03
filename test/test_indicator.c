#include "unity_fixture.h"

#include "../main/indicator.h"
#include "driver/gpio.h"
#include "mockgpio.h"

#define LEDPIN 16
#define TWENTYCM 1160

void booth_logic(uint64_t echotime);

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

TEST(Indicator, indicator_on_sets_gpio_high)
{
    indicator_on(true);

    const gpio_set_level_value_t *actual_output = gpio_set_level_call_with_values(0);
    TEST_ASSERT_EQUAL_INT(LEDPIN, actual_output->gpio_num);
    TEST_ASSERT_EQUAL_INT(1, actual_output->level);
}

TEST(Indicator, indicator_on_sets_gpio_low)
{
    indicator_on(false);

    const gpio_set_level_value_t *actual_output = gpio_set_level_call_with_values(0);
    TEST_ASSERT_EQUAL_INT(LEDPIN, actual_output->gpio_num);
    TEST_ASSERT_EQUAL_INT(0, actual_output->level);
}

TEST(Indicator, indicator_led_pin_high_when_distance_less_than_20cm)
{
    indicator_initialize(LEDPIN);
    booth_logic(TWENTYCM - 100);

    const gpio_set_level_value_t *actual_output = gpio_set_level_call_with_values(0);
    TEST_ASSERT_EQUAL_INT(1, actual_output->level);
}

TEST(Indicator, indicator_led_pin_low_when_distance_is_over_20cm)
{
    indicator_initialize(LEDPIN);
    booth_logic(TWENTYCM + 100);

    const gpio_set_level_value_t *actual_output = gpio_set_level_call_with_values(0);
    TEST_ASSERT_EQUAL_INT(0, actual_output->level);
}

TEST_GROUP_RUNNER(Indicator)
{
    RUN_TEST_CASE(Indicator, indicator_initialize_setup_gpio);
    RUN_TEST_CASE(Indicator, indicator_on_sets_gpio_high);
    RUN_TEST_CASE(Indicator, indicator_on_sets_gpio_low);
    RUN_TEST_CASE(Indicator, indicator_led_pin_high_when_distance_less_than_20cm);
    RUN_TEST_CASE(Indicator, indicator_led_pin_low_when_distance_is_over_20cm);
}