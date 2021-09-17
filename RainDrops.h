
#ifndef RAIN_DROPS_H
#define RAIN_DROPS_H

#include "Scene.h"

#define DROP_COUNT 32

class RainDrops : public Scene {
  
public:
  RainDrops(Palette* palette) : palette(palette) {
    tailSize = palette->size;

    for (byte i = 0; i < DROP_COUNT; i++) {
      dropCounts[i] = displayH + random(10);
    }
  }
  
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;

      for (byte i = 0; i < DROP_COUNT; i++) {
        pos[i] = ((pos[i] + 1) + dropCounts[i]) % dropCounts[i];
        
      }
      
    }
  }

  virtual void draw() override {
    if (!reInit && isOtherDisplay) {
      for (byte i = 0; i < DROP_COUNT; i++) {
        dropCounts[i] = displayH + random(10);
      }
      reInit = true;
    }
    
    matrix.startWrite();
    for (byte j = 0; j < DROP_COUNT; j++) {
      for (byte i = 0; i < (tailSize + 1); i++) {
        
          color_t color = i >= tailSize ? CLEAR : palette->colors[i];
          byte dropCount = dropCounts[j];
          int p = ((pos[j] - i) + dropCount) % dropCount;
          
          matrix.writePixel(j, p, color);
      }
    }
    matrix.endWrite();
  }


private:
  byte tailSize;
  byte pos[DROP_COUNT];

  byte dropCounts[DROP_COUNT];

  Palette* palette;

  bool reInit = false;
};

#endif //RAIN_DROPS_H
