

#ifndef PALETTE_H
#define PALETTE_H

#include "ColorsAndMatrix.h"

class Palette {
  public:
  
  Palette(byte size, color_t* colors) : size(size), colors(colors) {
  }

  Palette() {}
  
  Palette(uint16_t color_a, uint16_t color_b, uint16_t color_c) {
    size = 3;
    colors = (color_t*)malloc(sizeof(color_t)*size);
    colors[0] = color_a;
    colors[1] = color_b;
    colors[2] = color_c;
  }

  virtual ~Palette() {
    free(colors);
  }

  Palette(byte size, byte r, byte g, byte b) : size(size) {
    
    colors = (color_t*)malloc(sizeof(color_t)*size);
    
    for (byte i = 0; i < size; i++) {

      float fsize = (float)size;
      float fratio = ((fsize - i)/fsize);
      
      colors[i] = COLOR(fratio * r, fratio * g, fratio * b);
    }
  }

public:
  byte size;
  color_t* colors;
};

class RainbowPalette : public Palette {
  public:
  RainbowPalette() : Palette() {
    size = 12;
    colors = (color_t*)malloc(sizeof(color_t)*size);

    colors[0] = COLOR(7,0,0);
    colors[1] = COLOR(7,4,0);
    colors[2] = COLOR(7,7,0);
    colors[3] = COLOR(4,7,0);
    colors[4] = COLOR(0,7,0);
    colors[5] = COLOR(0,7,4);
    colors[6] = COLOR(0,7,7);
    colors[7] = COLOR(0,4,7);
    colors[8] = COLOR(0,0,7);
    colors[9] = COLOR(4,0,7);
    colors[10] = COLOR(7,0,7);
    colors[11] = COLOR(7,0,4);
  }
};

class VuPalette : public Palette {
  public:
  VuPalette() : Palette() {
    size = 4;
    colors = (color_t*)malloc(sizeof(color_t)*size);
    colors[0] = COLOR(0,0,7);
    colors[1] = COLOR(0,7,0);
    colors[2] = COLOR(7,7,0);
    colors[3] = COLOR(7,0,0);
  }
};


#endif //PALETTE_H
