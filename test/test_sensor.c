#include "unity_fixture.h"
#include <stdbool.h>

#include "../main/sensor.h"
#include "esp_timer.h"
#include <driver/gpio.h>
#include <mockesp_timer.h>
#include <mockgpio.h>
#include <mockqueue.h>
#include <mocktask.h>
#include <mocktime.h>

#define PIN GPIO_NUM_4
#define TRIGGERPIN GPIO_NUM_16
#define TRIGGERPERIOD 1000000

TEST_GROUP(Sensor);

TEST_SETUP(Sensor) {
  gpio_mock_initialize();
  initialize_queue_mocking();
  initialize_esp_timer_mocking();
}

TEST_TEAR_DOWN(Sensor) {}

TEST(Sensor, initializeSensor_InitializesSensorPin) {
  initialize_sensor(PIN);
  const gpio_config_t *g = gpio_config_called_with();
  TEST_ASSERT_NOT_NULL(g);
  TEST_ASSERT_EQUAL_INT(GPIO_INTR_NEGEDGE, g->intr_type);
  TEST_ASSERT_EQUAL_INT64(1ULL << PIN, g->pin_bit_mask);
  TEST_ASSERT_EQUAL_INT(GPIO_MODE_INPUT, g->mode);
  TEST_ASSERT_EQUAL_INT(GPIO_PULLUP_DISABLE, g->pull_up_en);
  TEST_ASSERT_EQUAL_INT(GPIO_PULLDOWN_ENABLE, g->pull_down_en);
}

TEST(Sensor, initialize_sensor_AddsISRHandler) {
  initialize_sensor(PIN);
  gpio_handler_value_t *v = get_gpio_handler_value();
  TEST_ASSERT_EQUAL_INT(PIN, v->gpio_num);
  TEST_ASSERT_EQUAL_PTR(sensor_isr_handler, v->isr_handler);
  TEST_ASSERT_EQUAL_PTR((void *)PIN, v->args);
}

TEST(Sensor, initializeTrigger_startTimer) {
  initialize_sensor(PIN);
  esp_timer_handle_t timer;
  initialize_trigger(TRIGGERPIN, &timer);
  esp_timer_create_call_value_t *tc = esp_timer_create_called_with();

  TEST_ASSERT_NOT_NULL(tc->create_args);
  TEST_ASSERT_NOT_NULL(tc->out_handle);
  TEST_ASSERT_EQUAL_PTR(periodic_timer_callback, tc->create_args->callback);

  esp_timer_start_periodic_value_t *tp = esp_timer_start_periodic_called_with();
  TEST_ASSERT_EQUAL_INT(TRIGGERPERIOD, tp->period);

  // This ensures that the timer we started is the timer that we passed to
  // esp_timer_create
  TEST_ASSERT_EQUAL_PTR(timer, tp->timer);
}

TEST(Sensor, initialize_calls_xQueueCreate) {
  xQueueCreate_will_return(0x4);
  QueueHandle_t hdl = initialize_sensor(PIN);
  TEST_ASSERT_EQUAL_PTR(0x4, hdl);
  TEST_ASSERT_TRUE(xQueueCreate_was_called());
  xQueueCreate_value_t *q = xQueueCreate_called_with();
  TEST_ASSERT_EQUAL_INT(sizeof(int64_t), q->uxItemSize);
}

TEST(Sensor, handle_interrupt_returns_time_spend_high) {
  esp_timer_get_time_will_return(100);
  set_gpio_level(1);
  sensor_isr_handler((void *)PIN);

  esp_timer_get_time_will_return(200);
  set_gpio_level(0);
  sensor_isr_handler((void *)PIN);

  int64_t time_difference = get_queue_send_value();
  TEST_ASSERT_EQUAL_INT64(100, time_difference);
}

TEST(Sensor, periodic_timer_callback_triggersEcho) {

  periodic_timer_callback((void *)TRIGGERPIN);

  const gpio_set_level_value_t *l = gpio_set_level_call_with_values(0);
  TEST_ASSERT_EQUAL_INT(TRIGGERPIN, l->gpio_num);
  TEST_ASSERT_EQUAL_INT(1, l->level);

  const gpio_set_level_value_t *l1 = gpio_set_level_call_with_values(1);
  TEST_ASSERT_EQUAL_INT(TRIGGERPIN, l1->gpio_num);
  TEST_ASSERT_EQUAL_INT(0, l1->level);

  int calledLength = gpio_set_level_call_values_length();
  TEST_ASSERT_EQUAL_INT(2, calledLength);

  useconds_t u = usleep_was_called_with();
  TEST_ASSERT_EQUAL_INT(10, u);
}

TEST_GROUP_RUNNER(Sensor) {
  RUN_TEST_CASE(Sensor, initializeSensor_InitializesSensorPin);
  RUN_TEST_CASE(Sensor, initialize_sensor_AddsISRHandler);
  RUN_TEST_CASE(Sensor, initializeTrigger_startTimer);
  RUN_TEST_CASE(Sensor, initialize_calls_xQueueCreate);
  RUN_TEST_CASE(Sensor, handle_interrupt_returns_time_spend_high);
  RUN_TEST_CASE(Sensor, periodic_timer_callback_triggersEcho);
}
