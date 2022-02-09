
#ifndef TURNSTILE_H
#define TURNSTILE_H

#define CLEAR_OFFSET 32

#include "Scene.h"

class Turnstile : public Scene {
  
public:
  Turnstile(Palette* palette) : palette(palette) {

  }

  virtual ~Turnstile() {
     delete palette;
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;

      offset = (offset + 2) % ((displayH + 1) + (32 + 1));
    }
  }

  void makeLine(int off, color_t color) {

    off = off % ((displayH + 1) + (32 + 1));
    
    const byte width = displayW/2;

    const byte yOffset = fmin(off, (displayH + 1));
    int xOffset = fmax(0, off - (displayH + 1));

    matrix.drawLine(xOffset, displayH - yOffset, width - xOffset, -1 + yOffset , color);
  }

  virtual void draw() override {
    
    makeLine(offset + CLEAR_OFFSET, COLOR(0,0,0));
    makeLine(offset + CLEAR_OFFSET + 1, COLOR(0,0,0));
    makeLine(offset, COLOR(0,0,7));
    makeLine(offset + 1, COLOR(0,0,7));
    
  }


private:
  Palette* palette;

  int offset = 0;

};

#endif //TURNSTILE_H
