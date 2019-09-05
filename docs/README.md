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

## Helpful Information

* [Creating Tests](creating-tests.md)
* [Interrupts](interrupts.md)
* [Platform Specific Headers](platform-specific-headers.md)