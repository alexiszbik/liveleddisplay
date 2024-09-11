
#ifndef ARROWS_H
#define ARROWS_H

#include "Scene.h"
#include "Palette.h"

#define ARROW_SIZE 2

class Arrows : public Scene {

public:

  Arrows() {
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      setNeedsRefresh();
      xPos[0] = ((xPos[0] + 1) + maxXPos) % maxXPos;
      xPos[1] = ((xPos[1] - 1) + maxXPos) % maxXPos;
    }
  }

    virtual void draw() override {
        matrix.startWrite();

        byte size = displayHalfW/ARROW_SIZE;

        for (byte display = 0; display < 2; display++) {

            bool isOtherDisplay = display == 1;

            for (byte a = 0; a < size; a++) {
                byte pixX = 0;

                byte colorIdx = a;
                if (isOtherDisplay) {
                    colorIdx = size - 1 - a;
                }

                color_t color = HSV((1535/size) * colorIdx, 255, 255);
                
                for (byte y = 0; y < displayH; y++) {

                    byte x = (pixX + xPos[display] + a*ARROW_SIZE + maxXPos) % (maxXPos);
                    if (isOtherDisplay) {
                        x += displayHalfW;
                    }
                    
                    matrix.writeFastHLine(x, y, ARROW_SIZE, color);
            
                    if (y == displayHalfH - 1) {
            
                    } else if (y > displayHalfH - 1) {
                        isOtherDisplay ? pixX++ : pixX--;
                    } else {
                        isOtherDisplay ? pixX-- : pixX++;
                    }
                }
            }

        }

    matrix.endWrite();
    }


private:
  
  byte xPos[2] = {0,0};
  byte maxXPos = displayW/2;

};

#endif //ARROWS_H
