
#ifndef EXPLODE_H
#define EXPLODE_H

#include "Scene.h"

class Explode : public TickerScene {
  
  public:
    Explode(){}
    
  virtual void draw() override {
      if (isOtherDisplay) {
          randomSeed(444);
      }
      bool state = getRandom() % 2;
      matrix.fillRect(0,0,displayHalfW,displayH, state ? COLOR(7, 7, 7) : clearColor());
  }
    
};

#endif //FLASHING_SIGN_H
