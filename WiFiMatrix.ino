#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

#include "./src/Matrix.h"
#include "./src/00_TreeAnimation.h"
#include "./src/01_SnakeAnimation.h"
#include "./src/02_ChessAnimation.h"
#include "./src/03_WaterAnimation.h"
#include "./src/04_NewYear2025.h"
#include "./src/05_Apricode.h"
#include "./src/Index.h"
#include "./src/Utils.h"

#define LATCH_PIN_COMMON    D3    // ST_CP (12)
#define DATA_PIN_POSITIVE   D6    // DS (14)
#define CLOCK_PIN_POSITIVE  D5    // SH_CP (11)
#define DATA_PIN_NEGATIVE   D4    // DS (14)
#define CLOCK_PIN_NEGATIVE  D2    // SH_CP (11)
#define LEFT_BUTTON         D8
#define RIGHT_BUTTON        D7

#define EE_DELAY_ADDR       1
#define EE_ANIM_ADDR        32

byte activeFrame[8];
uint16_t framesDelay = 300;

uint32_t now;
uint32_t lastFrameChange = 0;
uint8_t frameIndex = 0;
uint8_t framesCount = 1;
uint8_t animationIndex = 0;
uint8_t animationsCount = 6;

bool leftButtonState = false;
bool rightButtonState = false;
bool leftButtonPrevState = false;
bool rightButtonPrevState = false;

byte* activeAnimation[64];

void setup() {
  pinMode(LATCH_PIN_COMMON, OUTPUT);
  pinMode(DATA_PIN_POSITIVE, OUTPUT);
  pinMode(CLOCK_PIN_POSITIVE, OUTPUT);
  pinMode(DATA_PIN_NEGATIVE, OUTPUT);
  pinMode(CLOCK_PIN_NEGATIVE, OUTPUT);

  pinMode(LEFT_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);

  digitalWrite(LATCH_PIN_COMMON, HIGH);

  EEPROM.begin(2048);

  EEPROM.get(EE_DELAY_ADDR, framesDelay);
  EEPROM.get(EE_ANIM_ADDR, animationIndex);

  framesDelay = constrain(framesDelay, 100, 1000);
  animationIndex = constrain(animationIndex, 0, animationsCount);

  defineAnimation();
}

void loop() {
  leftButtonState = digitalRead(LEFT_BUTTON);
  rightButtonState = digitalRead(RIGHT_BUTTON);

  if (leftButtonState && !leftButtonPrevState) {
    framesDelay += 100;
    if (framesDelay > 1000) {
      framesDelay = 100;
    }

    EEPROM.put(EE_DELAY_ADDR, framesDelay);
    EEPROM.commit();
  }

  if (rightButtonState && !rightButtonPrevState) {
    animationIndex = (animationIndex + 1) % animationsCount;
    EEPROM.put(EE_ANIM_ADDR, animationIndex);
    EEPROM.commit();
    defineAnimation();
  }

  defineFrame();
  drawFrame(activeFrame);

  leftButtonPrevState = leftButtonState;
  rightButtonPrevState = rightButtonState;
}

void defineAnimation()
{
  switch(animationIndex) {
    case 0:
      memcpy(activeAnimation, treeAnimation, 8 * sizeof(byte*));
      framesCount = 8;
      break;
    case 1:
      memcpy(activeAnimation, SnakeAnimation, 22 * sizeof(byte*));
      framesCount = 22;
      break;
    case 2:
      memcpy(activeAnimation, ChessAnimation, 2 * sizeof(byte*));
      framesCount = 2;
      break;
    case 3:
      memcpy(activeAnimation, WaterAnimation, 33 * sizeof(byte*));
      framesCount = 33;
      break;
    case 4:
      memcpy(activeAnimation, NewYear2025Animation, 3 * sizeof(byte*));
      framesCount = 3;
      break;
    case 5:
      memcpy(activeAnimation, ApricodeAnimation, 8 * sizeof(byte*));
      framesCount = 8;
      break;
  }
}

void defineFrame()
{
  now = millis();
  if (lastFrameChange + framesDelay > now) {
    return;
  }
  lastFrameChange = millis();

  for (int i = 0; i < 8; i++) {
    activeFrame[i] = activeAnimation[frameIndex][i];
  }

  frameIndex = (frameIndex + 1) % framesCount;
}

void drawFrame(byte frame[8]) {
  for (int i = 7; i >= 0; i--) {
    sendMatrixByte(frame[i], i);
  }
}

void sendMatrixByte(byte val, byte row)
{
  // MSBFIRST
  // LSBFIRST
  digitalWrite(LATCH_PIN_COMMON, LOW);
  shiftOut(DATA_PIN_POSITIVE, CLOCK_PIN_POSITIVE, MSBFIRST, val);
  shiftOut(DATA_PIN_NEGATIVE, CLOCK_PIN_NEGATIVE, MSBFIRST, refernceMatrix[row]);
  digitalWrite(LATCH_PIN_COMMON, HIGH);
}
