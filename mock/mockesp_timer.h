#ifndef _MOCK_ESP_TIMER_H_
#define _MOCK_ESP_TIMER_H_

#include "esp_timer.h"

typedef struct
{
    const esp_timer_create_args_t *create_args;
    esp_timer_handle_t *out_handle;
} esp_timer_create_call_value_t;

typedef struct
{
    esp_timer_handle_t timer;
    uint64_t period;
} esp_timer_start_periodic_value_t;

void initialize_esp_timer_mocking();

esp_timer_create_call_value_t *esp_timer_create_called_with();

esp_timer_start_periodic_value_t *esp_timer_start_periodic_called_with();

#endif