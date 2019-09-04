# Creating Your First Test

## Testing Framework

The testing framework we have selected is [Unity](http://www.throwtheswitch.org/unity).  It is already used internally by the esp-idf framework.

The Unity source code is included in the repository, under the [`/unity`](https://github.com/PillarTechnology/phonebooth-esp-idf/tree/master/unity) folder.  There is also a shell script, [`source-library.sh`](https://github.com/PillarTechnology/phonebooth-esp-idf/blob/master/unity/source-library.sh), which will update to the latest version of the library.

## Writing the First Test

### What Will We Test? And Why?

The setup step for an LED is to configure the controlling GPIO pin for output.  We do this by setting three values on a `gpio_config_t` structure:

* `pin_bit_mask` should be set to a bit mask of the pins this config applies to.  To create a bitmask for the esp32 pins, left-shift a 1 to the pin number, e.g. `pin_bit_mask = 1ULL << 7` would create a bit mask for pin 7, and assign it to a variable `pin_bit_mask`.
* `mode` should be set to `GPIO_MODE_OUTPUT`.
* `intr_type` should be set to `GPIO_INTR_DISABLE`.  We'll need to learn about interupts later, but the topic only applies to input pins.

### Boilerplate
Dealing with hardware usually comes in two steps.  First, you need to configure the hardware in a setup or initialization step.  Then you can use the hardware in the main body of your program.  The simplest hardware component that we will use is an LED, which is turned on when the distance sensor indicates that the phone booth is occupied, and turned off when the phone booth is empty.

In the test folder, create a file `test_led.c`.

You'll need to create a test-suite around the led.  The boilerplate looks like this:

``` C
#include "unity_fixture.h"

#include "../main/led.h"
#include "driver/gpio.h"

TEST_GROUP(Led);

TEST_SETUP(Led) {}

TEST_TEAR_DOWN(Led) {}

TEST_GROUP_RUNNER(Led) {}
```

### Making it Fail

The next step is to write a test which confirms that those values where set on a `gpio_config_t` structure, and a pointer to that structure was passed to `gpio_config()`.  A test might look like this:

``` C

TEST(Led, initialized_SetsGpioForOutput)
{
    initialize_led(12);

    const gpio_config_t *g = // ! How do I find out what gpio_config was called with?

    TEST_ASSERT_EQUAL_INT(1ULL << LEDPIN, g->pin_bit_mask);
    TEST_ASSERT_EQUAL_INT(GPIO_MODE_OUTPUT, g->mode);
    TEST_ASSERT_EQUAL_INT(GPIO_INTR_DISABLE, g->intr_type);
}

[...]

TEST_GROUP_RUNNER(Led)
{
    RUN_TEST_CASE(Led, initialized_SetsGpioForOutput);
}
```

### Mocking a Dependency

Now we begin to need a framework for mocking dependencies in C.

We need three things to make this mock work:

1. A mock implementation of the `esp_err_t gpio_config(const gpio_config_t *pGPIOConfig)` dependency which stores what it was called with.
2. A function to retrieve the stored value e.g. `gpio_config_called_with()`
3. A function to ensure that the stored value is set to a known state at the start of each test e.g. `mockgpio_initialize()`

Under the `/mock` directory, create a file `mockgpio.h`. We'll add the following to `mockgpio.h`:

``` C
#ifndef _MOCKGPIO_H_
#define _MOCKGPIO_H_

#include <driver/gpio.h>

const gpio_config_t *gpio_config_called_with();

void mockgpio_initialize();

#endif
```

We will add an implementation for `gpio_config_called_with` inside of `mock/gpio.c`

Modify `mock/gpio.c` to include `mockgpio.h` at the top e.g.
``` C
[...]
#include "mockgpio.h"
[...]
```
Now we can work on the implementations.

This is a simple implementation:

``` C
#include <string.h>

gpio_config_t gpio_config_called_value;

esp_err_t gpio_config(const gpio_config_t* pGPIOConfig)
{
    // Copy the actual value, rather than storing the pointer.
    // The pointer may point to a local variable in the calling function, 
    // and the contents may be overwritten as soon as the calling function 
    // exits.  Learn from our pain.
    memcpy(&gpio_config_called_value, pGPIOConfig, sizeof(gpio_config_t));
}

const gpio_config_t* gpio_config_called_with()
{
    return &gpio_config_called_value;
}

void mockgpio_initialize()
{
    // Zero out the block of memory before each test case.
    memset(&gpio_config_called_value, 0, sizeof(gpio_config_t));
}
```

Now we can modify our tests to use the new mock we created.

``` C

[...]

#define LEDPIN GPIO_NUM_4

[...]

TEST_SETUP(Led) { mockgpio_initialize(); }

[...]

TEST(Led, initialized_SetsGpioForOutput)
{
    initialize_led(12);

    const gpio_config_t *g = gpio_config_called_with();

    TEST_ASSERT_EQUAL_INT(1ULL << LEDPIN, g->pin_bit_mask);
    TEST_ASSERT_EQUAL_INT(GPIO_MODE_OUTPUT, g->mode);
    TEST_ASSERT_EQUAL_INT(GPIO_INTR_DISABLE, g->intr_type);
}
```

## Commands to run the test

We need to create an executable to run the test

``` bash
$ mkdir tdd
$ cd tdd
$ cmake .. -DTDD=true
$ make && ./test/phonebooth-esp-idf-test

```

Congrats! We've successfully failed out first test:

``` bash
~/workspace/phonebooth-esp-idf/tdd (task-11)$ make && test/phonebooth-esp-idf-test 
[ 33%] Built target unity
[100%] Built target phonebooth-esp-idf-test
Unity test run 1 of 1
./Users/clayton.c.dowling/workspace/phonebooth-esp-idf/test/test_led.c:20:TEST(Led, initialized_SetsGpioForOutput):FAIL: Expected 16 Was 0


-----------------------
1 Tests 1 Failures 0 Ignored 
FAIL
```

## Making Our Test Pass
 ... 

``` bash
# Passing output goes here
```

## Link to branch with finished examples, for reference
