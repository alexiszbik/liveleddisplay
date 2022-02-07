
#ifndef OSC_H
#define OSC_H

#include "Scene.h"

class Osc : public Scene {
  
public:
  Osc(Palette* palette) : palette(palette) {
    waveCount = palette->size;
  }

  virtual ~Osc() {
      delete palette;
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;
      offset = (offset + 1) % displayW; 
    }
  }

  virtual void draw() override {
      const byte w = displayW/2;

      //clearScreen();

      for (byte i = 0; i < w; i++) {
        for (byte s = 0; s < waveCount; s++) {

          color_t c = palette->colors[s];
          byte waveOffset = (displayW/waveCount) * s;
          
          float x = ((float)(i + offset + waveOffset + (isOtherDisplay ? displayW/2 : 0)))/(float)w;
          float y = cos(PI*x) * displayH/2 + displayH/2; 
          y = fmin(y,displayH - 1);

          float off_x = -1.0/(float)w;
          float prevy = cos(PI*(x+off_x)) * displayH/2 + displayH/2; 
          prevy = fmin(prevy,displayH - 1);

          if (prevy != y) {
            matrix.drawPixel(i, prevy, COLOR(0,0,0));
          }
                    
          matrix.drawPixel(i, y, c);
        }
      }
  }

private:
  byte offset = 0;
  byte waveCount = 0;
  Palette* palette;
};


#endif //OSC_H
