
#ifndef STICKS_H
#define STICKS_H

#include "Scene.h"
#include "Palette.h"

class Sticks : public AutoRefreshedScene {
  
public:
  Sticks(Palette* palette) : palette(palette)  {
    tailSize = palette->size;
  }

  virtual ~Sticks() {
     delete palette;
  }
  
public:
    virtual void updateOffsets() override {
        xPos = ((xPos + 1 * direction()) + maxStickCount) % maxStickCount;
    }

  virtual void draw() override {

    for (byte i = 0; i < tailSize * space; i++) {
      
      byte x = ((xPos - i * direction()) + maxStickCount) % maxStickCount;
      
      color_t color = (i % space == 0) ? palette->colors[(int)ceil(i/space)] : COLOR(0, 0, 0);
      
      matrix.fillRect(x * width, 0, width, displayH, color);
    }
    
  }

private:
  int direction() {
    return (isOtherDisplay ? 1 : -1);
  }

  byte width = 2;
  byte tailSize;
  const byte space = 2;
  
  byte xPos = 0;
  
  byte maxStickCount = displayW/2/width;

  Palette* palette;

};

#endif //STICKS_H
