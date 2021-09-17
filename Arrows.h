
#ifndef ARROWS_H
#define ARROWS_H

#include "Scene.h"
#include "Palette.h"

class Arrows : public Scene {

public:

  Arrows(Palette* palette) : palette(palette)  {
    arrowsSize = palette->size;
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;

      xPos = ((xPos - 1) + maxXPos) % (maxXPos);

    }
  }

  virtual void draw() override {
    matrix.startWrite();

    for (byte a = 0; a < arrowsSize + 1; a++) {
      
      byte pixX = 0;
      
      for (byte y = 0; y < displayH; y++) {
        color_t color = a < arrowsSize ? palette->colors[a] : CLEAR;
  
        byte halfDisplay = displayH/2;
  
        byte x = (pixX + xPos + a*2 + maxXPos) % (maxXPos);
        
        matrix.writeFastHLine(x, y, 2, color);
  
        if (y == halfDisplay - 1) {
  
        } else if (y > halfDisplay - 1) {
          pixX++;
        } else {
          pixX--;
        }
      }
      
    }
    
    matrix.endWrite();

  }


private:
  byte arrowsSize;
  Palette* palette;

  byte xPos = 0;
  byte maxXPos = displayW/2;

};

#endif //ARROWS_H
