## Issues we encountered

* Read gpio documentation and configure pins correctly, for example:
  * GPIO 6-11 are for flash (DO NOT USE)
  * GPIO 34, 35, 36, and 39 are input only
  * When wifi is used, GPIO 0, 2, 15, 13, 12, 14, 27, 25, 26 cannot be used
* Variables on the stack dissapear and are overwritten when they are out of scope
  * Variables that must persist should be declared on the heap
* Pass pointers to structures between methods, then copy the contents when you use it
* Incrementally flash and test hardware
  * printf is very helpful when debugging the hardware with idf monitor
* Check polarity of components (see image with LED)
* :squirrel: