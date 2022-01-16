
#ifndef OSC_H
#define OSC_H

#include "Scene.h"

class Osc : public Scene {
  
public:
  Osc() {
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;
      offset = (offset + 1) % displayW;
      
    }
  }

  virtual void draw() override {
      byte w = displayW/2;

      clearScreen();

      for (byte i = 0; i < w; i++) {
        float x = ((float)(i + offset + (isOtherDisplay ? displayW/2 : 0)))/(float)w;
        float y = cos(PI*x) * displayH/2 + displayH/2; 
        
        matrix.drawPixel(i, y, COLOR(0,4,7));
      }
      
  }

private:
  byte offset = 0;
};


#endif //OSC_H
