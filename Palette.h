

#ifndef PALETTE_H
#define PALETTE_H

#include "ColorsAndMatrix.h"

class Palette {
  public:
  
  Palette(byte size, color_t* colors) : size(size), colors(colors) {
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

#endif //PALETTE_H
