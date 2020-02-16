/**
 *  TM1637 v0.0.1 (2020.02.16)
 *  https://github.com/TeWu/TM1637
 **/


#ifndef _TM1637_SEGMENTS_PATTERNS_H_
#define _TM1637_SEGMENTS_PATTERNS_H_ 1


//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     --- .
//      D

//=== Decimal digits
//                       .GFEDCBA
#define TM1637_SPAT_0  0b00111111
#define TM1637_SPAT_1  0b00000110
#define TM1637_SPAT_2  0b01011011
#define TM1637_SPAT_3  0b01001111
#define TM1637_SPAT_4  0b01100110
#define TM1637_SPAT_5  0b01101101
#define TM1637_SPAT_6  0b01111101
#define TM1637_SPAT_7  0b00000111
#define TM1637_SPAT_8  0b01111111
#define TM1637_SPAT_9  0b01101111

//=== Letters
//                       .GFEDCBA
#define TM1637_SPAT_A  0b01110111
#define TM1637_SPAT_b  0b01111100
#define TM1637_SPAT_c  0b01011000
#define TM1637_SPAT_C  0b00111001
#define TM1637_SPAT_d  0b01011110
#define TM1637_SPAT_e  0b01111011
#define TM1637_SPAT_E  0b01111001
#define TM1637_SPAT_F  0b01110001
#define TM1637_SPAT_G  0b00111101
#define TM1637_SPAT_h  0b01110100
#define TM1637_SPAT_H  0b01110110
#define TM1637_SPAT_i  0b00010000
#define TM1637_SPAT_I  0b00110000
#define TM1637_SPAT_J  0b00011110
#define TM1637_SPAT_L  0b00111000
#define TM1637_SPAT_n  0b01010100
#define TM1637_SPAT_N  0b00110111
#define TM1637_SPAT_o  0b01011100
#define TM1637_SPAT_P  0b01110011
#define TM1637_SPAT_q  0b01100111
#define TM1637_SPAT_r  0b01010000
#define TM1637_SPAT_S  0b01101101
#define TM1637_SPAT_t  0b01111000
#define TM1637_SPAT_T  0b00110001
#define TM1637_SPAT_u  0b00011100
#define TM1637_SPAT_U  0b00111110
#define TM1637_SPAT_y  0b01101110
#define TM1637_SPAT_Z  0b01011011

//=== Misc
//                                 .GFEDCBA
#define TM1637_SPAT_BLANK        0
#define TM1637_SPAT_FULL         0b11111111
#define TM1637_SPAT_DOT          0b10000000
#define TM1637_SPAT_MINUS        0b01000000
#define TM1637_SPAT_DEGREE       0b01100011
#define TM1637_SPAT_HAT          0b00100011
#define TM1637_SPAT_QUOTE        0b00100010
#define TM1637_SPAT_APOSTROPHE   0b00100000
#define TM1637_SPAT_OPEN_PAREN   0b00111001
#define TM1637_SPAT_CLOSE_PAREN  0b00001111

//=== Bars
//                              .GFEDCBA
#define TM1637_SPAT_HBAR_T    0b00000001  // Top horizontal bar
#define TM1637_SPAT_HBAR_M    0b01000000  // Middle horizontal bar
#define TM1637_SPAT_HBAR_B    0b00001000  // Bottom horizontal bar
#define TM1637_SPAT_HBAR_TM   0b01000001  // Top and Middle horizontal bars
#define TM1637_SPAT_HBAR_TB   0b00001001  // Top and Bottom horizontal bars
#define TM1637_SPAT_HBAR_MB   0b01001000  // Middle and Bottom horizontal bars
#define TM1637_SPAT_HBAR_TMB  0b01001001  // Top, Middle and Bottom horizontal bars
#define TM1637_SPAT_VBAR_L    0b00110000  // Left vertical bar
#define TM1637_SPAT_VBAR_R    0b00000110  // Right vertical bar
#define TM1637_SPAT_VBAR_LR   0b00110110  // Left and Right vertical bar


#endif /* _TM1637_SEGMENTS_PATTERNS_H_ */