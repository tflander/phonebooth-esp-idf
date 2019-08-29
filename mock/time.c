#include "newlib/time.h"

useconds_t usleep_call_value;

void initialize_time_mocking()
{
    usleep_call_value = 0;
}

int usleep(useconds_t us)
{
    usleep_call_value = us;
    return 0;
}

useconds_t usleep_was_called_with()
{
    return usleep_call_value;
}
