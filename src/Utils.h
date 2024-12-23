#ifndef Utils_h
#define Utils_h

#include <Arduino.h>

byte hatoi(char* num)
{
    int8_t len = strlen(num);
    uint8_t exp = 1;
    byte val = 0;

    for (int8_t i = len - 1; i >= 0 ; i--) {
        switch (num[i]) {
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                val += (num[i] - '0') * exp;
                break;
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
                val += (num[i] - 'A' + 10) * exp;
                break;
        }

        exp *= 16;
    }

    return val;
}

void composeFrame(char* income, byte* frame, int8_t len)
{
    char num[3];
    for (int i = 0; i < len; i++) {
        num[0] = income[2 * i];
        num[1] = income[2 * i + 1];
        num[2] = '\0';

        frame[i] = hatoi(num);
    }
}

#endif