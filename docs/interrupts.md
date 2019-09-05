# Interrupts
## What is an interrupt?
* When a program is running and an event occurs, it may trigger an interrupt
* The interrupt handler pauses the execution of the current program and runs code that was triggered by the interrupt
* After the interrupt code has finished running, the previously paused program continues

## How to configure an interrupt
1. Follow the [gpio sample](https://github.com/espressif/esp-idf/blob/master/examples/peripherals/gpio/main/gpio_example_main.c) on the espressif github
1. Configure a gpio input pin to trigger an interrupt
1. Create a queue to handle the events that occur from the pin
1. Start gpio task
1. Initialize gpio isr service
1. Configure gpio service to the pin 

For more information you can also see [Tasks and Queues](tasks-and-queues.md).

## Tips on writing interrupts
* Keep them as small in complexity and time as possible
* We do not want an interrupt to trigger when the current interrupt is occuring
* DON'T use a printf inside an isr handler (this might trigger a serial interrupt)
