# Phone Booth ESP-IDF Learning Lab

## Description

The hardware and software product from this lab will be a phone booth occupancy
detector, similar in concept to the phone booth occupancy detectors present in
our Ann Arbor office.

## Objective

Build and test drive a device which uses an [esp32](https://docs.espressif.com/projects/esp-idf/en/latest/hw-reference/get-started-devkitc.html) microcontroller and a 
[HC-SR04](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf) 
ultrasonic range finder to tell if a phone booth is occupied.

* The phone booth is occupied if the distance detected by the range finder is 
  less than 20cm.
* If the phone booth is occupied, an LED should be turned on.
* If the phone booth is *not* occupied, the LED should *not* be turned on.

### Materials

* [Click here](materials.md)

## Intended Audience

You have some previous experience with integrated hardware/software
development.  You are also interested in stretching your capabilities.

## Prerequisites

* Some knowledge of C software development.
* A workstation with a working native C compiler.
* [CMake](https://cmake.org/).
* The [esp-idf](https://docs.espressif.com/projects/esp-idf/en/stable/get-started/) toolkit.

The lab uses CMake, a build configuration tool.  CMake lets use describe what the outcomes of 
our build should be, and then generates appropriate build files to make that happen.  You will
not need to fully understand CMake, and should not need to modify the build system to complete
this lab.  If you would like to understand the build system better, we have annotated the 
CMakeLists.txt files in each directory to make the intention of each command clear.

## What You Will Learn

1. How to write software for the esp32 platform using the native SDK.
1. How to write tests against system functions.
1. How to manually mock functions and system header files in a project.


## Issues we encountered

* Do not use GPIO 2 as an output pin (board uses this and will reset)
* Variables on the stack dissapear and are overwritten when they are out of scope
  * Variables that must persist should be declared on the heap
* Pass pointers to structures between methods, then copy the contents when you use it
* Incrementally flash and test hardware
  * printf is very helpful when debugging the hardware with idf monitor
* Check polarity of components (see image with LED)
* :squirrel:

## Interrupts
### What is an interrupt?
* When a program is running and an event occurs, it may trigger an interrupt
* The interrupt handler pauses the execution of the current program and runs code that was triggered by the interrupt
* After the interrupt code has finished running, the previously paused program continues

### How to configure an interrupt
1. Follow the [gpio sample](https://github.com/espressif/esp-idf/blob/master/examples/peripherals/gpio/main/gpio_example_main.c) on the espressif github
1. Configure a gpio input pin to trigger an interrupt
1. Create a queue to handle the events that occur from the pin
1. Start gpio task
1. Initialize gpio isr service
1. Configure gpio service to the pin 

### Tips on writing interrupts
* Keep them as small in complexity and time as possible
* We do not want an interrupt to trigger when the current interrupt is occuring
* DON'T use a printf inside an isr handler (this might trigger a serial interrupt)
