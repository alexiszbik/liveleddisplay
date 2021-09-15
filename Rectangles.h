
#ifndef RECTANGLES_H
#define RECTANGLES_H

#include "Scene.h"
#include "Palette.h"

class Rectangles : public Scene {
  
public:
  Rectangles(Palette* palette) : palette(palette)  {
    rectCount = palette->size;
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;

      pos = (pos + 1) % (maxPos);
    }
  }

  virtual void draw() override {

    for (byte i = 0; i < (rectCount + 1); i++) {
        byte p = ((pos - i) + maxPos) % maxPos;

        color_t color = i == rectCount ? CLEAR : palette->colors[i];
        
        matrix.drawRect(p, p, displayW/2 - p*2, displayH - p*2, color);

    }
  }

private:
  byte rectCount;
  byte pos = 0;

  const byte maxPos = (displayH/2);

  Palette* palette;

};

#endif //RECTANGLES_H
