#include "unity_fixture.h"
#include <stdbool.h>

#include "../main/sensor.h"

TEST_GROUP(Sensor);

TEST_SETUP(Sensor) {}

TEST_TEAR_DOWN(Sensor) {}

TEST(Sensor, test_initialize_sensor)
{
    bool result = initialize_sensor(); // TODO: This needs a GPIO pin number
    TEST_ASSERT_TRUE(result);
}

TEST_GROUP_RUNNER(Sensor)
{
    RUN_TEST_CASE(Sensor, test_initialize_sensor);
}
