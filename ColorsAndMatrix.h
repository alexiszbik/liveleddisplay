
#ifndef COLOR_H
#define COLOR_H

#define CLK  8  
#define OE   9
#define LAT 10
#define A   A0
#define B   A2
#define C   A1

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
#include <RGBmatrixPanel.h>
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
#else

#include "../Source/Matrix.h"

#endif

#define displayW (32 * 2)
#define displayHalfW 32
#define displayH 16
#define displayHalfH 8


typedef uint16_t color_t;

#define COLOR(r,g,b) matrix.Color333(r,g,b)
//#define CLEAR COLOR(0, 0, 0)

static inline color_t clearColor() {
  return 0;
}


static inline void clearScreen() {
  matrix.fillScreen(clearColor());
}


#endif //COLOR_H
