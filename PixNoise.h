
#ifndef PIXNOISE_H
#define PIXNOISE_H

#include "Scene.h"
#include "Palette.h"

class PixNoise : public AutoRefreshedScene {

public:

  PixNoise() {
  }
  
public:

  byte getRandomColor() {
    return (byte)min(((random(1000) % 2) * 4), 7);
  }

  void makePixel() {
    byte x = random(displayW);
    byte y = random(displayH);
    color_t c = COLOR(getRandomColor(), getRandomColor(), getRandomColor());
    matrix.writePixel(x, y, random(4) >= 3 ? clearColor() : c);
  }
  
  virtual void draw() override {
    matrix.startWrite();

    for (byte i = 0; i < 64; i++) {
      makePixel();
    }

    matrix.endWrite();
  }


private:

};

#endif //PIXNOISE_H
