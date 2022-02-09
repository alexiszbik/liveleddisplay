
#ifndef OSC_H
#define OSC_H

#include "Scene.h"

#define NO_VALUE 100

#define START_NOTE 48
#define VU_H 16
#define VU_W 16

class Osc : public Scene {
  
public:
  Osc(Palette* palette) : palette(palette) {
    waveCount = palette->size;
    buf = (byte*)malloc(sizeof(byte)*waveCount);
  }

  virtual ~Osc() {
      delete palette;
      free(buf);
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;
      offset = (offset + 1) % displayW; 
    }
  }

  virtual void midiNote(byte noteValue) override {

    if (noteValue >= START_NOTE && noteValue <= (START_NOTE + 3))
    {
      squareMode = true;
      squarePosition = noteValue - START_NOTE;
      needRefresh = true;
    } else {
      if (squareMode) {
        needsClear = true;
      }
      squareMode = false;
      needRefresh = true;
    }
 
  }

  virtual void draw() override {

    if (squareMode) {
      if (xSqr >= 0) {
        matrix.fillRect(xSqr, 0, VU_W, VU_H, COLOR(0,0,0));
      }

      byte colorIndex = random(1000) % palette->size;
      color_t c = palette->colors[colorIndex];

      xSqr = isOtherDisplay ? (((int)squarePosition - 2) * (int)VU_W) : (int)squarePosition * (int)VU_W;
      
      if (xSqr >= 0) {
        matrix.fillRect(xSqr, 0, VU_W, VU_H, c);
      }
      
      
    } else {
      if (needsClear) {
        if (xSqr >= 0) {
          matrix.fillRect(xSqr, 0, VU_W, VU_H, COLOR(0,0,0));
        }
        needsClear = false;
      }
      
      const byte w = displayW/2;

      for (byte i = 0; i < w; i++) {
        
        for (byte s = 0; s < waveCount; s++) {

          byte waveOffset = (displayW/waveCount) * s;
          
          float x = ((float)(i + offset + waveOffset + (isOtherDisplay ? displayW/2 : 0)))/(float)w;
          float y = cos(PI*x) * displayH/2 + displayH/2; 
          y = fmin(y,displayH - 1);

          float off_x = -1.0/(float)w;
          float prevy = cos(PI*(x+off_x)) * displayH/2 + displayH/2; 
          prevy = fmin(prevy,displayH - 1);

          matrix.drawPixel(i, prevy, COLOR(0,0,0));
          buf[s] = y;
        }

        for (byte s = 0; s < waveCount; s++) {
          color_t c = palette->colors[s];
          matrix.drawPixel(i, buf[s], c);
        }
      }
    }
  }

private:
  byte offset = 0;
  byte waveCount = 0;
  byte* buf;
  Palette* palette;

  bool squareMode = false;
  bool needsClear = false;
  byte squarePosition = 0;

  int xSqr = 0;
};


#endif //OSC_H
