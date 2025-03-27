
#ifndef COLOR_H
#define COLOR_H

#define CLK  8  
#define OE   9
#define LAT 10
#define A   A0
#define B   A2
#define C   A1

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) //for Arduino Uno

#include <RGBmatrixPanel.h>
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);


#elif defined(ARDUINO_SAMD_ZERO) //for Arduino Zero
#include <Adafruit_Protomatter.h>
uint8_t rgbPins[]  = {2, 3, 4, 5, 6, 7};
uint8_t addrPins[] = {A0, A2, A1};
uint8_t clockPin   = 8;
uint8_t latchPin   = 10;
uint8_t oePin      = 9;

static Adafruit_Protomatter matrix(
  64, 4, 1, rgbPins, 3, addrPins, clockPin, latchPin, oePin, true);

#else //for Testing Local
#include "../Source/Matrix.h"

#endif

#define displayW 64
#define displayHalfW 32
#define displayH 16
#define displayHalfH 8


#if defined(ARDUINO_SAMD_ZERO) 
#define COLOR(r,g,b) matrix.color565(r*35,g*35,b*35)
#define HSV(h,s,v) matrix.colorHSV(h * 42, s, v)
#else 
#define COLOR(r,g,b) matrix.Color333(r,g,b)
#define HSV(h,s,v) matrix.ColorHSV(h, s, v, true)
#endif

typedef uint16_t color_t;

//#define CLEAR COLOR(0, 0, 0)

static inline color_t clearColor() {
  return 0;
}

static inline void clearScreen() {
  matrix.fillScreen(clearColor());
}


#endif //COLOR_H
