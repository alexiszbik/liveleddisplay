
#ifndef TURNSTILE_H
#define TURNSTILE_H

#define CLEAR_OFFSET 32

#include "Scene.h"

class Turnstile : public AutoRefreshedScene {
  
public:
  Turnstile() {
  }

  virtual ~Turnstile() {
  }
  
public:
  virtual void updateOffsets() override {
      offset = (offset + 2) % ((displayH + 1) + (64 + 1));
  }

  void makeLine(int off, color_t color) {
    
    off = off % ((displayH + 1) + (64 + 1));
    
    const byte width = displayW/2;

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
    
    for (byte i = 0; i < 2; i++) {
      makeLine(offset + CLEAR_OFFSET + i, clearColor());
      makeLine(offset + i, COLOR(0,0,7));
    }
    
  }


private:

  int offset = 0;

};

#endif //TURNSTILE_H
