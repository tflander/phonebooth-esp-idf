#include "esp_timer.h"
#include "mockesp_timer.h"
#include <string.h>

int64_t time;

esp_timer_create_call_value_t esp_timer_create_call_value;

esp_timer_start_periodic_value_t esp_timer_start_periodic_value;

void initialize_esp_timer_mocking()
{
  time = 0;
  memset((void *)&esp_timer_create_call_value, 0,
         sizeof(esp_timer_create_call_value_t));
  memset((void *)&esp_timer_start_periodic_value, 0,
         sizeof(esp_timer_start_periodic_value_t));
}

void esp_timer_get_time_will_return(int64_t return_value)
{
  time = return_value;
}

int64_t esp_timer_get_time() { return time; }

esp_err_t esp_timer_create(const esp_timer_create_args_t *create_args,
                           esp_timer_handle_t *out_handle)
{
  esp_timer_create_call_value.create_args = create_args;
  esp_timer_create_call_value.out_handle = out_handle;
  return ESP_OK;
}

esp_err_t esp_timer_start_periodic(esp_timer_handle_t timer, uint64_t period)
{
  esp_timer_start_periodic_value.timer = timer;
  esp_timer_start_periodic_value.period = period;
  return ESP_OK;
}

esp_timer_create_call_value_t *esp_timer_create_called_with()
{
  return &esp_timer_create_call_value;
}

esp_timer_start_periodic_value_t *esp_timer_start_periodic_called_with()
{
  return &esp_timer_start_periodic_value;
}
