# Phone Booth ESP-IDF Learning Lab

## Description

The hardware and software product from this lab will be a phone booth occupancy
detector, similar in concept to the phone booth occupancy detectors present in
our Ann Arbor office.

## Intended Audience

You have some previous experience with integrated hardware/software
development.  You are also interested in stretching your capabilities.

## Prerequisites

* Some knowledge of C software development.
* A workstation with a working native C compiler.
* CMake.
* The [esp-idf](https://docs.espressif.com/projects/esp-idf/en/stable/get-started/) toolkit.

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
* 
