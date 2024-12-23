#ifndef TreeAnimation_h
#define TreeAnimation_h

#include <Arduino.h>

byte tree0[8] {
    0b00000010,
    0b00001001,
    0b00100101,
    0b10010101,
    0b10010101,
    0b00100101,
    0b00001001,
    0b00000010,
};

byte tree1[8] {
    0b00000010,
    0b00001001,
    0b00000101,
    0b11010101,
    0b11010101,
    0b00000101,
    0b00001001,
    0b00000010,
};

// tree2 == tree0

byte tree3[8] {
    0b00000010,
    0b00000001,
    0b00100101,
    0b11010101,
    0b11010101,
    0b00100101,
    0b00000001,
    0b00000010,
};

// tree4 == tree0

byte tree5[8] {
    0b00000000,
    0b00001001,
    0b00100101,
    0b11010101,
    0b11010101,
    0b00100101,
    0b00001001,
    0b00000000,
};

// tree6 == tree0

byte tree7[8] {
    0b00000000,
    0b00000001,
    0b00000101,
    0b11010101,
    0b11010101,
    0b00000101,
    0b00000001,
    0b00000000,
};

byte* treeAnimation[8] {
    tree0,
    tree1,
    tree0,
    tree3,
    tree0,
    tree5,
    tree0,
    tree7,
};

#endif
