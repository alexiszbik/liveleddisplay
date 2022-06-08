
#ifndef PIXNOISE_H
#define PIXNOISE_H

#include "Scene.h"
#include "Palette.h"

class PixNoise : public Scene {

public:

  PixNoise() {
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;
    }
  }

  byte getRandomColor(bool isOtherDisplay) {
    return (byte)min(((random(1000 + (isOtherDisplay ? 100 : 0)) % 2) * 4), 7);
  }
  
  virtual void draw() override {
    matrix.startWrite();

    for (byte i = 0; i < 32; i++) {
      byte x = random(displayW/2);
      byte y = random(displayH);
      color_t c = COLOR(getRandomColor(isOtherDisplay), getRandomColor(isOtherDisplay), getRandomColor(isOtherDisplay));
      if (random(4) >= 3) {
        matrix.writePixel(x, y, COLOR(0,0,0));
      } else {
        matrix.writePixel(x, y, c);
      }
      
    }

    matrix.endWrite();
  }


private:

};

#endif //PIXNOISE_H
