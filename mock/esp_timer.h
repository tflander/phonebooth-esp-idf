#ifndef _ESP_TIMER_H_
#define _ESP_TIMER_H_

#include <stdint.h>
void esp_timer_get_time_will_return(int64_t);

int64_t esp_timer_get_time();

#endif