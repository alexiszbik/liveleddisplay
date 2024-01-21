
#ifndef SQUARE_TRAIL_H
#define SQUARE_TRAIL_H

#include "Scene.h"

class SquareTrail : public AutoRefreshedScene {
  
public:
  SquareTrail(Palette* palette, bool mirror = false) : palette(palette), mirror(mirror) {
    squareCount = palette->size;
    wCount = displayW/size;
    if (mirror) {
      wCount = wCount / 2;
    }
    posMax = wCount * displayH/size;
  }

  virtual ~SquareTrail() {
     delete palette;
  }
  
  
public:
  virtual void updateOffsets() override {
    pos = ((pos + 1 * direction()) + posMax) % posMax;
  }

  virtual void draw() override {

    for (byte i = 0; i < (squareCount + 1); i++) {
        color_t color = i == squareCount ? clearColor() : palette->colors[i];

        int p = ((pos - i * direction()) + posMax) % posMax;

        int y = ceil(p / wCount);
        int x = p % wCount;
        int xOffset = mirror ? 0 : (isOtherDisplay ? displayW/2 : 0);

        matrix.fillRect(x * size - xOffset, y * size, size, size, color);
    }
  }

private:
  int direction() {
    return mirror ? (isOtherDisplay ? -1 : 1) : 1;
  }

private:
  byte squareCount;

  const byte size = 4;
  byte pos = 0;

  byte wCount;
  byte posMax;

  Palette* palette;
  bool mirror = false;
};

#endif //SQUARE_TRAIL_H
