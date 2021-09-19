
#ifndef SQUARE_DROPS_H
#define SQUARE_DROPS_H

#include "Scene.h"

#define SQR_SIZE 4
#define SQR_COUNT 32

class SquareDrops : public Scene {
  
public:
  SquareDrops(Palette* palette) : palette(palette) {
    colorCount = palette->size;

    for (byte i = 0; i < SQR_COUNT; i++) {
      states[i] = random(1000) % (colorCount + 1);
    }
  }
  
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;

      if (isOtherDisplay) {
        randomSeed(5555);
      }

      for (byte i = 0; i < SQR_COUNT; i++) {
        states[i] = (states[i] + 1) % (colorCount + random(10));
      }
    }
  }

  virtual void draw() override {
    
    if (!reInit && isOtherDisplay) {
      for (byte i = 0; i < SQR_COUNT; i++) {
        states[i] = random(1000) % (colorCount + 1);
      }
      reInit = true;
    }

    for (byte j = 0; j < displayH/SQR_SIZE; j++) {
      for (byte i = 0; i < displayW/2/SQR_SIZE; i++) {

        byte index = i + j * (displayW/2/SQR_SIZE);
        byte colorIndex = states[index];

        color_t color = colorIndex >= colorCount ? CLEAR : palette->colors[colorIndex];
      
        matrix.fillRect(i * SQR_SIZE, j * SQR_SIZE, SQR_SIZE, SQR_SIZE, color);
      }
    }
  }


private:
  byte colorCount;
  byte states[SQR_COUNT];
  
  Palette* palette;

  bool reInit = false;
};

#endif //SQUARE_DROPS_H
