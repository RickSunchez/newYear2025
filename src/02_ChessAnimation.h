#ifndef ChessAnimation_h
#define ChessAnimation_h

#include <Arduino.h>

byte chess0[8] {
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
};

byte chess1[8] {
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
};

byte* ChessAnimation[2] {
    chess0,
    chess1,
};

#endif
