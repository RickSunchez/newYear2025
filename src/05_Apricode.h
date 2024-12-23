#ifndef Apricode_h
#define Apricode_h

#include <Arduino.h>

byte apricode0[8] {
    0b00000000,
    0b11111110,
    0b01111100,
    0b00111110,
    0b00011111,
    0b00001101,
    0b00000100,
    0b00000000,
};

byte apricode1[8] {
    0b00000000,
    0b00111110,
    0b00111100,
    0b00111110,
    0b00011111,
    0b00001101,
    0b00000100,
    0b00000000,
};

// apricode2 = apricode0

byte apricode3[8] {
    0b00000000,
    0b11111110,
    0b01111100,
    0b00111110,
    0b00000011,
    0b00000001,
    0b00000000,
    0b00000000,
};

// apricode4 = apricode0

byte apricode5[8] {
    0b00000000,
    0b11100010,
    0b01100000,
    0b00100010,
    0b00011111,
    0b00001101,
    0b00000100,
    0b00000000,
};

// apricode6 = apricode0

byte apricode7[8] {
    0b00000000,
    0b11111110,
    0b01000100,
    0b00100110,
    0b00010111,
    0b00001101,
    0b00000100,
    0b00000000,
};

byte* ApricodeAnimation[8] {
    apricode0,
    apricode1,
    apricode0,
    apricode3,
    apricode0,
    apricode5,
    apricode0,
    apricode7,
};

#endif
