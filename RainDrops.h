
#ifndef RAIN_DROPS_H
#define RAIN_DROPS_H

#include "Scene.h"

#define DROP_COUNT displayW

class RainDrops : public AutoRefreshedScene {
  
public:
  RainDrops(Palette* palette) : palette(palette) {
    tailSize = palette->size;

    for (byte i = 0; i < DROP_COUNT; i++) {
      dropCounts[i] = displayH + random(10);
    }
  }

  virtual ~RainDrops() {
     delete palette;
  }
  
public:
   virtual void updateOffsets() override {
      for (byte i = 0; i < DROP_COUNT; i++) {
        pos[i] = ((pos[i] + 1) + dropCounts[i]) % dropCounts[i];
        
      }
  }

  virtual void draw() override {
    
    matrix.startWrite();
    for (byte j = 0; j < DROP_COUNT; j++) {
      for (byte i = 0; i < (tailSize + 1); i++) {
        
          color_t color = i >= tailSize ? clearColor() : palette->colors[i];
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
};

#endif //RAIN_DROPS_H
