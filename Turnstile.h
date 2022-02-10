
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

      //offset = (offset + 2) % ((displayH + 1) + (32 + 1));

      offset = (offset + 2) % ((displayH + 1) + (64 + 1));
    }
  }

  void makeLine(int off, color_t color) {

    //off = off % ((displayH + 1) + (32 + 1));

    off = off % ((displayH + 1) + (64 + 1));
    
    const byte width = displayW/2;

    /*
    const byte yOffset = fmin(off, (displayH + 1));
    int xOffset = fmax(0, off - (displayH + 1));

    matrix.drawLine(xOffset, displayH - yOffset, width - xOffset, -1 + yOffset , color);*/

    if (off < ((displayH + 1) + (32 + 1))) {
      const byte yOffset = fmin(off, (displayH + 1));
      int xOffset = fmax(0, off - (displayH + 1));

      if (isOtherDisplay) {
          matrix.drawLine(0, displayH/2, width - xOffset, -1 + yOffset , color);
      } else {
          matrix.drawLine(width, displayH/2, xOffset, displayH - yOffset , color);
      }
      
    } else {
      int xOffset = off - ((displayH + 1) + (32 + 1));

      if (isOtherDisplay) {
        matrix.drawLine(0, displayH/2, xOffset, 0, color);
      } else {
        matrix.drawLine(width, displayH/2, width - xOffset, displayH, color);
      }
    }
    
  }

  virtual void draw() override {
    
    makeLine(offset + CLEAR_OFFSET + 16, COLOR(0,0,0));
    makeLine(offset + CLEAR_OFFSET + 16 + 1, COLOR(0,0,0));
    makeLine(offset, COLOR(0,0,7));
    makeLine(offset + 1, COLOR(0,0,7));
    
  }


private:
  Palette* palette;

  int offset = 0;

};

#endif //TURNSTILE_H
