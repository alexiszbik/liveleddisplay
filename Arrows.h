
#ifndef ARROWS_H
#define ARROWS_H

#include "Scene.h"
#include "Palette.h"

#define SIZE 2

class Arrows : public Scene {

public:

  Arrows() {
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;
      xPos = ((xPos - 1 * (isOtherDisplay ? 1 : -1)) + maxXPos) % (maxXPos);
    }
  }

  virtual void draw() override {
    matrix.startWrite();

    for (byte a = 0; a < displayW/2/SIZE; a++) {
      byte pixX = 0;

      byte c = a;
      if (isOtherDisplay) {
        c = displayW/2/SIZE - 1 - a;
      }

      color_t color = matrix.ColorHSV((1535/(displayW/2/SIZE)) * c, 255, 255, true);
      
      for (byte y = 0; y < displayH; y++) {

        byte halfDisplay = displayH/2;

        byte x = (pixX + xPos + a*SIZE + maxXPos) % (maxXPos);
        
        matrix.writeFastHLine(x, y, SIZE, color);
  
        if (y == halfDisplay - 1) {
  
        } else if (y > halfDisplay - 1) {
          isOtherDisplay ? pixX++ : pixX--;
        } else {
          isOtherDisplay ? pixX-- : pixX++;
        }
      }
    }
    
    matrix.endWrite();
  }


private:
  
  byte xPos = 0;
  byte maxXPos = displayW/2;

};

#endif //ARROWS_H
