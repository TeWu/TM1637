#ifndef _TM1637_H_
#define _TM1637_H_ 1

#include <inttypes.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include "pin_config.h"
#include "segments_patterns.h"


#define TM1637_DIGITS_COUNT  4

#define TM1637_CMD_SETUP           0b01000000
#define TM1637_CMD_SET_DATA        0b11000000
#define TM1637_CMD_SET_BRIGHTNESS  0b10000000

#define TM1637_MASK_POS             0b11
#define TM1637_MASK_BRIGHTNESS_REG  0b1111
#define TM1637_MASK_BRIGHTNESS      0b0111
#define TM1637_MASK_ON_OFF          0b1000


#define TM1637_QUARTER_CLOCK_PERIOD  100  // In microseconds (us)
#define TM1637_QUARTER_CYCLE_DELAY  _delay_us(TM1637_QUARTER_CLOCK_PERIOD)
#define TM1637_HALF_CYCLE_DELAY     _delay_us(2 * TM1637_QUARTER_CLOCK_PERIOD)
#define TM1637_COMM_START  TM1637_SET_DIO_LOW_AND_OUTPUT; TM1637_HALF_CYCLE_DELAY  // Pull DIO LOW - send START
#define TM1637_COMM_STOP   TM1637_SET_CLK_LOW_AND_OUTPUT; TM1637_QUARTER_CYCLE_DELAY;  /* Pull CLK LOW, to let TM1637 know that it can stop sending ACK (that is, it can stop pulling DIO LOW) */\
                           TM1637_SET_DIO_LOW_AND_OUTPUT; TM1637_QUARTER_CYCLE_DELAY;  /* Make sure DIO is LOW, because we need rising edge transition */\
                           TM1637_SET_CLK_HIGH_AND_INPUT; TM1637_HALF_CYCLE_DELAY;     /* Let the CLK be pulled HIGH by pullup resistor */\
                           TM1637_SET_DIO_HIGH_AND_INPUT; TM1637_HALF_CYCLE_DELAY      /* Let the DIO be pulled HIGH - send STOP */

#define TM1637_SET_CLK_LOW_AND_OUTPUT  TM1637_DDR |=  (1 << TM1637_CLK)
#define TM1637_SET_CLK_HIGH_AND_INPUT  TM1637_DDR &= ~(1 << TM1637_CLK)
#define TM1637_SET_DIO_LOW_AND_OUTPUT  TM1637_DDR |=  (1 << TM1637_DIO)
#define TM1637_SET_DIO_HIGH_AND_INPUT  TM1637_DDR &= ~(1 << TM1637_DIO)
#define TM1637_READ_DIO                bit_is_set(TM1637_PIN, TM1637_DIO)


extern const uint8_t TM1637_digitToSegment[];
uint8_t TM1637_brightness_reg;


void TM1637_init(void);
void TM1637_turnOnOff(uint8_t on);
void TM1637_turnOn(void);
void TM1637_turnOff(void);
void TM1637_setBrightness(uint8_t brightness);
void TM1637_turnOnAndSetBrightness(uint8_t brightness);
void TM1637_setSegments(const uint8_t segments[], uint8_t length, uint8_t pos);
void TM1637_clear(void);

uint8_t TM1637_displayDecNumber(int16_t num);
void    TM1637_displayDigits(const uint8_t digits[], uint8_t length, uint8_t pos);

#endif /* _TM1637_H_ */