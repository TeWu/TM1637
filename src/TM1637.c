/**
 *  TM1637 v0.0.1 (2020.02.16)
 *  https://github.com/TeWu/TM1637
 **/


#include "TM1637.h"


const uint8_t TM1637_digitToSegment[] = {
  TM1637_SPAT_0,
  TM1637_SPAT_1,
  TM1637_SPAT_2,
  TM1637_SPAT_3,
  TM1637_SPAT_4,
  TM1637_SPAT_5,
  TM1637_SPAT_6,
  TM1637_SPAT_7,
  TM1637_SPAT_8,
  TM1637_SPAT_9,
  TM1637_SPAT_A,
  TM1637_SPAT_b,
  TM1637_SPAT_C,
  TM1637_SPAT_d,
  TM1637_SPAT_E,
  TM1637_SPAT_F
  };


static inline uint8_t TM1637_writeByte(uint8_t data) {
  // Write data byte
  for (uint8_t i = 0; i < 8; i++) {
    TM1637_SET_CLK_LOW_AND_OUTPUT;
    TM1637_QUARTER_CYCLE_DELAY;

    // Set data bit
    if (data & 1) TM1637_SET_DIO_HIGH_AND_INPUT;
    else TM1637_SET_DIO_LOW_AND_OUTPUT;
    TM1637_QUARTER_CYCLE_DELAY;

    TM1637_SET_CLK_HIGH_AND_INPUT;
    TM1637_HALF_CYCLE_DELAY;
    data >>= 1;
  }

  // Prepare for receiving acknowledgement
  TM1637_SET_CLK_LOW_AND_OUTPUT;
  TM1637_SET_DIO_HIGH_AND_INPUT;
  TM1637_HALF_CYCLE_DELAY;

  // Read acknowledgement
  TM1637_SET_CLK_HIGH_AND_INPUT;
  TM1637_QUARTER_CYCLE_DELAY;
  uint8_t ack = TM1637_READ_DIO;
  if (ack == 0)                     // Not strictly necessary, but it's a good idea
    TM1637_SET_DIO_LOW_AND_OUTPUT;  // to avoid unnecessary voltage changes on DIO when possible
  TM1637_QUARTER_CYCLE_DELAY;

  return ack;
}

void TM1637_init(void) {
  TM1637_SET_DIO_HIGH_AND_INPUT;
  TM1637_SET_CLK_HIGH_AND_INPUT;
  TM1637_PORT &= ~((1 << TM1637_DIO) | (1 << TM1637_CLK));

  // Write TM1637_CMD_SETUP
  TM1637_COMM_START;
  TM1637_writeByte(TM1637_CMD_SETUP);
  TM1637_COMM_STOP;
}

static inline void TM1637_writeBrightnessReg(void) {
  // Write TM1637_CMD_SET_BRIGHTNESS + TM1637_brightness_reg
  TM1637_COMM_START;
  TM1637_writeByte(TM1637_CMD_SET_BRIGHTNESS | (TM1637_brightness_reg & TM1637_MASK_BRIGHTNESS_REG));
  TM1637_COMM_STOP;
}

static inline void TM1637_turnOnOff_inline(uint8_t on) {
  TM1637_brightness_reg = (on ? TM1637_MASK_ON_OFF : 0) | (TM1637_brightness_reg & TM1637_MASK_BRIGHTNESS);
  TM1637_writeBrightnessReg();
}

void TM1637_turnOnOff(uint8_t on) {
  TM1637_turnOnOff_inline(on);
}

void TM1637_turnOn(void) {
  TM1637_turnOnOff_inline(1);
}

void TM1637_turnOff(void) {
  TM1637_turnOnOff_inline(0);
}

void TM1637_setBrightness(uint8_t brightness) {
  TM1637_brightness_reg = (TM1637_brightness_reg & TM1637_MASK_ON_OFF) | (brightness & TM1637_MASK_BRIGHTNESS);
  TM1637_writeBrightnessReg();
}

void TM1637_turnOnAndSetBrightness(uint8_t brightness) {
  TM1637_brightness_reg = TM1637_MASK_ON_OFF | (brightness & TM1637_MASK_BRIGHTNESS);
  TM1637_writeBrightnessReg();
}

void TM1637_setSegments(const uint8_t segments[], uint8_t length, uint8_t pos) {
  TM1637_COMM_START;
  // Write TM1637_CMD_SET_DATA + first digit address
  TM1637_writeByte(TM1637_CMD_SET_DATA | (pos & TM1637_MASK_POS));
  // Write data bytes
  for (uint8_t i = 0; i < length; i++)
    TM1637_writeByte(segments[i]);
  TM1637_COMM_STOP;
}

void TM1637_clear(void) {
  TM1637_COMM_START;
  TM1637_writeByte(TM1637_CMD_SET_DATA);
  // Write blank segment data bytes
  for (uint8_t i = 0; i < TM1637_DIGITS_COUNT; i++)
    TM1637_writeByte(TM1637_SPAT_BLANK);
  TM1637_COMM_STOP;
}


uint8_t TM1637_displayNumber(int32_t num, uint8_t base) {
  // Assume: 2 <= base <= 16
  if (num == 0) {
    TM1637_setSegments((uint8_t[]) { TM1637_SPAT_BLANK, TM1637_SPAT_BLANK, TM1637_SPAT_BLANK, TM1637_SPAT_0 }, 4, 0);
    return 0;
  }
  int16_t pos2 = base * base;
  int16_t pos3 = pos2 * base;
  // Check if number fits in 4 digits, or 3 digits + minus sign
  if (num <= -pos3 ||
      (base <  16 && num >= pos3 * base) ||
      (base == 16 && num >  0xFFFF)
     ) return 1;

  uint16_t abs_num = num < 0 ? -num : num;
  // Extract digits from num
  uint8_t data[4] = {
    (abs_num / pos3) % base,
    (abs_num / pos2) % base,
    (abs_num / base) % base,
     abs_num         % base
  };
  // Convert digits to segments
  uint8_t started = 0;
  for (uint8_t i = 0; i < 4; i++) {
    if (started || data[i]) {
      data[i] = TM1637_digitToSegment[data[i]];
      if (!started && num < 0)
        data[i - 1] = TM1637_SPAT_MINUS;
      started = 1;
    } else data[i] = TM1637_SPAT_BLANK;
  }
  TM1637_setSegments(data, 4, 0);
  return 0;
}

void TM1637_displayDigits(const uint8_t digits[], uint8_t length, uint8_t pos) {
  uint8_t segments[TM1637_DIGITS_COUNT];
  for (uint8_t i = 0; i < length; i++)
    segments[i] = TM1637_digitToSegment[digits[i]];
  TM1637_setSegments(segments, length, pos);
}