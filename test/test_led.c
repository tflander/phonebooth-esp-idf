#include "unity_fixture.h"

#include "../main/led.h"
#include "driver/gpio.h"
#include "mockgpio.h"

#define LEDPIN GPIO_NUM_4

TEST_GROUP(Led);

TEST_SETUP(Led) { mockgpio_initialize(); }

TEST_TEAR_DOWN(Led) {}

TEST(Led, initialized_SetsGpioForOutput) {
  initialize_led(12);

  const gpio_config_t *g = gpio_config_called_with();

  TEST_ASSERT_EQUAL_INT(1ULL << LEDPIN, g->pin_bit_mask);
  TEST_ASSERT_EQUAL_INT(GPIO_MODE_OUTPUT, g->mode);
  TEST_ASSERT_EQUAL_INT(GPIO_INTR_DISABLE, g->intr_type);
}

TEST_GROUP_RUNNER(Led) { RUN_TEST_CASE(Led, initialized_SetsGpioForOutput); }