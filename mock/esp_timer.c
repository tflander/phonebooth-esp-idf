#include "esp_timer.h"

int64_t time;

void esp_timer_get_time_will_return(int64_t return_value)
{
    time = return_value;
}

int64_t esp_timer_get_time()
{
    return time;
}