
#ifndef COLOR_H
#define COLOR_H

#define CLK  8  
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

#include <RGBmatrixPanel.h>

#define displayW 32 * 2
#define displayH 16

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

typedef uint16_t color_t;

#define COLOR(r,g,b) matrix.Color333(r,g,b)
#define CLEAR COLOR(0, 0, 0)


void clearScreen() {
  matrix.fillScreen(CLEAR);
}


const byte rainbowCount = 12;
color_t rainbow[rainbowCount] = {COLOR(7,0,0), COLOR(7,4,0), COLOR(7,7,0), COLOR(4,7,0), COLOR(0,7,0), COLOR(0,7,4), COLOR(0,7,7), COLOR(0,4,7), COLOR(0,0,7), COLOR(4,0,7), COLOR(7,0,7), COLOR(7,0,4)};

color_t randomColor() {
  byte chosen = random(rainbowCount);
  return rainbow[chosen];  

}

#endif //COLOR_H
