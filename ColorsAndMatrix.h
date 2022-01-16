
#ifndef COLOR_H
#define COLOR_H

#define CLK  8  
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

#include <RGBmatrixPanel.h>

#define displayW (32 * 2)
#define displayH 16

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

typedef uint16_t color_t;

#define COLOR(r,g,b) matrix.Color333(r,g,b)
#define CLEAR COLOR(0, 0, 0)


void clearScreen() {
  matrix.fillScreen(CLEAR);
}

/*


color_t randomColor() {
  byte chosen = random(rainbowCount);
  return rainbow[chosen];  

}*/

#endif //COLOR_H
