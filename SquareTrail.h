
#ifndef SQUARE_TRAIL_H
#define SQUARE_TRAIL_H

#include "Scene.h"

class SquareTrail : public Scene {
  
public:
  SquareTrail(Palette* palette) : palette(palette) {
    squareCount = palette->size;
  }
  
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;
          
      pos = ((pos + 1) + posMax) % posMax;
    }
  }

  virtual void draw() override {

    for (byte i = 0; i < (squareCount + 1); i++) {
        color_t color = i == squareCount ? CLEAR : palette->colors[i];

        int p = ((pos - i) + posMax) % posMax;

        int y = ceil(p / (displayW/size));
        int x = p % (displayW/size);

        matrix.fillRect(x * size, y * size, size, size, color);
    }
  }

private:
  byte squareCount;

  const byte size = 8;
  byte pos = 0;

  const byte posMax = displayW/size * displayH/size;

  Palette* palette;
};

#endif //SQUARE_TRAIL_H
