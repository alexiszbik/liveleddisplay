
#ifndef SQUARES_H
#define SQUARES_H

#include "Scene.h"

class Squares : public Scene {
  
public:
  Squares(bool randomMode = true) : randomMode(randomMode) {
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;

        prevXPos = xPos;
        prevYPos = yPos;

        if (randomMode) {
          
          while(prevXPos == xPos && prevYPos == yPos) {
            xPos = random(displayW/size);
            yPos = random(displayH/size);
          }
          
        } else {
          
          xPos = (xPos + 1) % (displayW/size);

          if (xPos == 0) {
           yPos = (yPos + 1) % (displayH/size);
          }
          
        }
      }
    }

    virtual void draw() override {
      byte half = isOtherDisplay ? ((displayW/size)/2) : 0;
      byte _xPos = xPos - half;
      byte _prevXPos = prevXPos - half;
    
      matrix.fillRect(_prevXPos * size, prevYPos * size , size, size, matrix.Color333(0, 0, 0));
      matrix.fillRect(_xPos * size, yPos * size, size, size, randomColor());
    }

private:
    const byte size = 8;

    byte xPos = 0;
    byte yPos = 0;

    byte prevXPos = 0;
    byte prevYPos = 0;

    bool randomMode = true;
};


#endif //SQUARES_H
