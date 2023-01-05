
#ifndef CIRCLES_H
#define CIRCLES_H

#include "Scene.h"
#include "Palette.h"

#define C_SIZE 12

class Circles : public Scene {

public:

  Circles(Palette* palette) : palette(palette) {
  }
  virtual ~Circles() {
    delete palette;
  }

public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;

      offset = (offset + 1) % C_SIZE;
    }
  }

  virtual void draw() override {
    for (byte i = 0; i < palette->size; i++) {
      int idx = (offset - i);
      byte r = (idx + C_SIZE) % C_SIZE;
      byte x = isOtherDisplay ? 0 : displayHalfW;
      matrix.drawCircle(x, displayH/2, r * 4, palette->colors[i]);
    }
    
  }

private:
  Palette* palette;

  byte offset = 0;

};

#endif //CIRCLES_H
