#include <util/delay.h>
#include "../src/TM1637.h"


#define WAIT_TIME 3000  // in milliseconds
#define DISPLAY_BRIGHTNESS 7
#define STARTUP_MESSAGE_SEGMENTS ((uint8_t[]) { TM1637_SPAT_BLANK, TM1637_SPAT_H, TM1637_SPAT_I, TM1637_SPAT_BLANK })


static inline void wait(void) {
  _delay_ms(WAIT_TIME);
}

static inline void w(void) {
  _delay_ms(WAIT_TIME * 0.1);
}

int main(void) {
  TM1637_init();
  TM1637_setSegments(STARTUP_MESSAGE_SEGMENTS, TM1637_DIGITS_COUNT, 0);
  TM1637_turnOnAndSetBrightness(DISPLAY_BRIGHTNESS);
  wait();

  while (1) {
    // Display "0123"
    TM1637_setSegments((uint8_t[]) { TM1637_SPAT_0, TM1637_SPAT_1, TM1637_SPAT_2, TM1637_SPAT_3 }, 4, 0);
    wait();
    // Display "4567"
    TM1637_displayDigits((uint8_t[]) { 4, 5, 6, 7 }, 4, 0);
    wait();
    // Display "  89"
    TM1637_displayDecNumber(89);
    wait();
    // Display "    "
    TM1637_clear();
    wait();
    // Display " 89 " - Adds "89" starting at position 1
    TM1637_displayDigits((uint8_t[]) { 8, 9 }, 2, 1);
    wait();
    // Display "789 " - Adds "7" at position 0
    TM1637_displayDigits((uint8_t[]) { 7 }, 1, 0);
    wait();
    // Display "789A" - Adds "A" at position 3
    TM1637_setSegment(TM1637_SPAT_A, 3);
    wait();
    // Show all 8 different brightness levels
    TM1637_setSegments((uint8_t[]) { TM1637_SPAT_FULL, TM1637_SPAT_FULL, TM1637_SPAT_FULL }, 3, 1);
    for (uint8_t i = 0; i < 8; i++) {
      TM1637_displayDigits((uint8_t[]) { i }, 1, 0);
      TM1637_setBrightness(i);
      wait();
    }
    // Display "HoLA"
    TM1637_setSegments((uint8_t[]) { TM1637_SPAT_H, TM1637_SPAT_o, TM1637_SPAT_L, TM1637_SPAT_A }, 4, 0);
    wait();
    // Blink the display
    for (uint8_t i = 0; i < 19; i++) {
      TM1637_turnOnOff(i % 2);
      w();
    }
    TM1637_clear();
    TM1637_turnOn();
    // Animation
    for (uint8_t i = 0; i < 29; i++) {
      TM1637_setSegment(TM1637_SPAT_MINUS, i % TM1637_DIGITS_COUNT);
      w();
      TM1637_setSegment(TM1637_SPAT_BLANK, i % TM1637_DIGITS_COUNT);
    }
    // Display "donE"
    TM1637_setSegments((uint8_t[]) { TM1637_SPAT_d, TM1637_SPAT_o, TM1637_SPAT_n, TM1637_SPAT_E }, 4, 0);
    wait();
  }

  return 0;
}