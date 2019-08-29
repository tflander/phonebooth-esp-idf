#ifndef _ESP_TIMER_H_
#define _ESP_TIMER_H_

#include <stdint.h>
#include "esp_err.h"

typedef void (*esp_timer_cb_t)(void *arg);

typedef struct esp_timer *esp_timer_handle_t;

typedef enum
{
    ESP_TIMER_TASK, //!< Callback is called from timer task
} esp_timer_dispatch_t;

typedef struct
{
    esp_timer_cb_t callback;              //!< Function to call when timer expires
    void *arg;                            //!< Argument to pass to the callback
    esp_timer_dispatch_t dispatch_method; //!< Call the callback from task or from ISR
    const char *name;                     //!< Timer name, used in esp_timer_dump function
} esp_timer_create_args_t;


esp_err_t esp_timer_create(const esp_timer_create_args_t *create_args,
                           esp_timer_handle_t *out_handle);

esp_err_t esp_timer_start_periodic(esp_timer_handle_t timer, uint64_t period);

void esp_timer_get_time_will_return(int64_t);

int64_t esp_timer_get_time();

#endif