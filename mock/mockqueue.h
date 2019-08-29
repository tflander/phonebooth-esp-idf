#ifndef _MOCKQUEUE_H_
#define _MOCKQUEUE_H_
#include <stdint.h>
#include <stdbool.h>

struct xQueueCreate_value
{
    uint32_t uxQueueLength;
    uint32_t uxItemSize;
};

struct xQueueCreate_value *xQueueCreate_called_with();
int64_t get_queue_send_value();
bool xQueueCreate_was_called();
void initialize_queue_mocking();

#endif