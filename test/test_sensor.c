#include "unity_fixture.h"
#include <stdbool.h>

TEST_GROUP(Sensor);

TEST_SETUP(Sensor) {}

TEST_TEAR_DOWN(Sensor) {}

TEST(Sensor, isalive_GivenLiveCellZeroNeighbors_ReturnsFalse)
{
    TEST_ASSERT_FALSE(false);
}

TEST_GROUP_RUNNER(Sensor)
{
    RUN_TEST_CASE(Sensor, isalive_GivenLiveCellZeroNeighbors_ReturnsFalse);
}
