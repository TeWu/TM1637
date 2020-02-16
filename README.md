AVR library for TM1637 (LED Display Driver)
=======
This is a lightweight AVR library for driving 7-segment display modules based on [TM1637][1] chip.
TM1637 chip uses custom 2-wire communication protocol, which is similar to I2C, but does not conform to I2C standard.
This library provides software implementation of this protocol.

![TM1637 chip](https://i.imgur.com/lFW3axJ.jpg)


Key Features
=======

* Control the display by setting raw segment values.
    * Predefined segment values for decimal numbers, letters and common symbols.
* Set either the whole display or any digit independently.
* Display decimal/hexadecimal (or generic base) numbers easily.
* Turn the display on/off.
* Control the brightness.
* Pure software implementation.

*Note: The TM1637 has also keyboard input capability, which is not implemented in this library.*


Pins Configuration
=======

Modules based on TM1637 chip provide two signal pins (`CLK` and `DIO`) and two power pins (`VCC` and `GND`):

* `VCC` and `GND` — Connect to power input (5V or 3.3V) and ground respectively.
* `CLK` — CLocK signal; connect to any digital pin on the AVR chip.
* `DIO` — Data Input and Output signal; connect to any digital pin on the AVR chip.

**IMPORTANT**: `CLK` and `DIO` pins must be pulled up to `VCC` by EXTERNAL pullup resistors. This library CAN NOT work without those pullup resistors! Developed and tested with 10k pullup resistors at 3.3V VCC.

Before using the library adjust pin configuration in [`src/pin_config.h`][2] file. Note that `CLK` and `DIO` pins must be on the same port.


Usage
=======

Minimum working example (displays `HEL0`):

```c
#include "TM1637/TM1637.h"

int main(void) {
    TM1637_init();
    TM1637_setSegments((uint8_t[]) { TM1637_SPAT_H, TM1637_SPAT_E, TM1637_SPAT_L, TM1637_SPAT_0 }, 4, 0);
    TM1637_turnOnAndSetBrightness(TM1637_MAX_BRIGHTNESS);

    while (1);
    return 0;
}
```

For more complete example, that is demonstrating operation of all the library's functions, please refer to the [`example/TM1637_example.c`][3] file.

For description of all the library's functions see [`src/TM1637.h`][4] file.



[1]: https://www.mcielectronics.cl/website_MCI/static/documents/Datasheet_TM1637.pdf
[2]: https://github.com/TeWu/TM1637/blob/master/src/pin_config.h
[3]: https://github.com/TeWu/TM1637/blob/master/example/TM1637_example.c
[4]: https://github.com/TeWu/TM1637/blob/master/src/TM1637.h#L50