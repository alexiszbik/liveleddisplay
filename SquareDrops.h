
#ifndef SQUARE_DROPS_H
#define SQUARE_DROPS_H

#include "Scene.h"

#define SQR_SIZE 4
#define SQR_COUNT 32

class SquareDrops : public AutoRefreshedScene {
  
public:
  SquareDrops(Palette* palette) : palette(palette) {
    colorCount = palette->size;
    initialize();
  }

  void initialize() {
    for (byte i = 0; i < SQR_COUNT; i++) {
      states[i] = getRandom() % (colorCount + 1);
    }
  }

  virtual ~SquareDrops() {
    delete palette;
  }
  
public:
   virtual void updateOffsets() override {
    if (isOtherDisplay) {
      randomSeed(5555);
    }

    for (byte i = 0; i < SQR_COUNT; i++) {
      states[i] = (states[i] + 1) % (colorCount + random(10));
    }
  }

  virtual void draw() override {
    
    if (!reInit && isOtherDisplay) {
      initialize();
      reInit = true;
    }

    for (byte j = 0; j < displayH/SQR_SIZE; j++) {
      for (byte i = 0; i < displayW/2/SQR_SIZE; i++) {

        byte index = i + j * (displayW/2/SQR_SIZE);
        byte colorIndex = states[index];

        color_t color = colorIndex >= colorCount ? clearColor() : palette->colors[colorIndex];
      
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
