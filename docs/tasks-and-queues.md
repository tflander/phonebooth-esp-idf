# Tasks and Queues

The esp32 chip uses FreeRTOS as its default operating system.  FreeRTOS enables asynchronous operation by creating tasks, which encapsulate a discrete bit of functionality.  It also has Interrupt Service Routines (ISRs) which are intended to respond quickly to events on hardware.  ISR uses the queues to communicate their information quickly to the tasks.

## The Code

``` C
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <esp_timer.h>

#define SIGNAL_PIN GPIO_NUM_4

static void signalprocessing_task(void *arg)
{
    uint64_t timeData;
    QueueHandle_t sq = (QueueHandle_t)arg;

    for (;;)
    {
        if (xQueueReceive(sq, &timeData, portMAX_DELAY))
        {
            printf("Signal received at %llu\n", timeData);
        }
    }
}

void signal_isr_handler(void *arg)
{
    QueueHandle_t sq = (QueueHandle_t)arg;

    int64_t signalTime = esp_timer_get_time();
    xQueueSendFromISR(sq, &signalTime, NULL);
}

void app_main(void)
{
    // Create the queue used to communicate between the ISR and the Task
    QueueHandle_t signalQueue = xQueueCreate(10, sizeof(int64_t));

    // Start the actual task which will process data from the ISR
    xTaskCreate(signalprocessing_task, "signalprocessor", 2048, (void*)signalQueue, 10, NULL);

    // Set up the signal pin to cause an interrupt on input
    gpio_conf_t p;
    p.pin_bit_mask = 1ULL << SIGNAL_PIN;
    p.intr_type = GPIO_INTR_POSEDGE;
    p.mode = GPIO_MODE_INPUT;
    p.pull_up_en = GPIO_PULLUP_ENABLE;
    p.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&p);

    // Install the ISR on the pin we just configured.   
    gpio_install_isr_service(0);
    gpio_install_handler_add(SIGNAL_PIN, signal_isr_handler, (void*)signalQueue);
}
```

## The Task

The function `signalprocessing_task(void *arg)` is the actual task.  The `arg` parameter can be anything, and it is passed to the task via the fourth parameter to [xTaskCreate](http://esp32.info/docs/esp_idf/html/dd/d3c/group__xTaskCreate.html).  In this example we have chosen to pass in the queue handle, but it could be anything.

Inside of the task, we can run some setup code, and then we can start looping forever, waiting for data from the queue that was passed in.  We read data with the [xQueueReceive](http://esp32.info/docs/esp_idf/html/db/d0d/group__xQueueReceive.html) function.  Note that the pointer passed as the second argument (pvBuffer) must be of the same size and type as the size declared as the second argument (uxItemSize) to [xQueueCreate](http://esp32.info/docs/esp_idf/html/da/ded/group__xQueueCreate.html).  These tasks have the time to take actions on the data they receive.  We're only printing it in this example, but that's actually something you can't do in the ISR.

## The Interrupt Service Routine

The ISR operates under some restrictions.  It needs to respond quickly, before other interrupts occur, and it cannot trigger interrupts of its own.  It's worth noting that you can't put debugging printf statements in an ISR, because that triggers a serial interrupt.

What it can do is put a message on a queue.  Once a message has been put on a queue the work of the ISR should be considered done.  Let a task perform any necessary processing on the data.

For more information see [Interrupts](interrupts.md)