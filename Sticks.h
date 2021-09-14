
#ifndef STICKS_H
#define STICKS_H

#include "Scene.h"

class Sticks : public Scene {
  
public:
  Sticks()  {
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;

      xPos = ((xPos + 1 * (isOtherDisplay ? -1 : 1)) + stickCount) % stickCount;
    }
  }

  virtual void draw() override {
    //clearScreen();
    
    for (byte i = 0; i < tailSize * space; i++) {
      
      byte x = ((xPos - i * (isOtherDisplay ? -1 : 1)) + stickCount) % stickCount;
      
      color_t color = (i % space == 0) ? COLOR(0, 0, 7 - ceil(i/space)) : COLOR(0, 0, 0);
      
      matrix.fillRect(x * width, 0, width, displayH, color);
      
    }
    
  }

private:
    byte width = 2;
    byte tailSize = 8;
    byte xPos = 0;
    byte space = 2;
    
    byte prevXPos = 0;
    byte stickCount = displayW/2/width;

};

#endif //STICKS_H
