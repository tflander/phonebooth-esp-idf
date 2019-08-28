#ifndef _MOCKQUEUE_H_
#define _MOCKQUEUE_H_
#include <stdint.h>
#include <stdbool.h>

int64_t get_queue_send_value();
bool xQueueCreate_was_called();
void initialize_queue_mocking();

#endif