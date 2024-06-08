
#ifndef PIXNOISE_H
#define PIXNOISE_H

#include "Scene.h"
#include "Palette.h"

class PixNoise : public AutoRefreshedScene {

public:

  PixNoise() {
  }
  
public:

  byte getRandomColor(bool isOtherDisplay) {
    return (byte)min(((random(1000 + (isOtherDisplay ? 100 : 0)) % 2) * 4), 7);
  }

  void makePixel() {
    byte x = random(displayHalfW);
    byte y = random(displayH);
    color_t c = COLOR(getRandomColor(isOtherDisplay), getRandomColor(isOtherDisplay), getRandomColor(isOtherDisplay));
    matrix.writePixel(x, y, random(4) >= 3 ? clearColor() : c);
  }
  
  virtual void draw() override {
    matrix.startWrite();

    for (byte i = 0; i < 32; i++) {
      makePixel();
    }

    matrix.endWrite();
  }


private:

};

#endif //PIXNOISE_H
