# Platform Specific Headers

With any embedded development you are likely to find platform specific headers that you don't have on your workstation except as part of the platform SDK.  You will be tempted to add the SDK include paths to your testing include folders.  *Resist this temptation!*  Embedded SDK headers will most likely include things which aren't supported by your workstation hardware.  Instead make a *mock header*.  

## Mock Headers

Create your own *mock headers* underneath the `mock` folder provided as part of this lab, with the same name and path.

| Include Statement  | File Location |
| ================== | ============= |
| #include <driver/gpio.h> | mock/driver/gpio.h |
| #include <esp_timer.h> | mock/esp_timer.h |

Inside those mock headers, copy the parts that you need from the actual headers.

### How Do I Know What I Need?

Fortunately, your compiler will be very helpful in identifying your shortcomings.

* Messages about missing header files:  Create the header file to match the path in your source.
* Messages about missing constants/enums/types: Copy the actual constant/enum/type from the actual header into your mock header.
* Messages about unknown system variables or registers: Create your own, global, static variable with the same name, but do not assign addresses (in the case of registers).

### How Do I Find Actual Values?

**Don't** use Google to find the values.  While this will definitely return _a_ value, there's a decent chance that the result will be misleading.  There are forks of esp-idf which have been created to meet specific needs at varying times, and there's a better than average chance that the one you get isn't the one you want.

**Do** search the [Espressif esp-idf repository](https://github.com/espressif/esp-idf/).  This is the authoritative source.  Be sure to grab everything you need, but not more than you need.