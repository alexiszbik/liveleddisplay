
#ifndef QUAD_VU_H
#define QUAD_VU_H

#include "Scene.h"

#define VU_COUNT 4

#define VU_H 16
#define VU_W 8

#define START_NOTE 48

class QuadVu : public TickerScene {
  
public:
  QuadVu(Palette* palette) : palette(palette)  {
  }

  virtual ~QuadVu() {
    delete palette;
  }
  
public:
  virtual void midiNote(byte noteValue) override {

    if (noteValue >= START_NOTE && noteValue <= (START_NOTE + 3))
    {
      byte vuIndex = noteValue - START_NOTE;
      vuStates[vuIndex].reset();
    }
  }

  virtual void draw() override {

    for (byte i = 0; i < VU_COUNT; i++) {
      
      byte x = isOtherDisplay ? (displayW/2 - ((i+1) * VU_W)) : i * VU_W;

      byte colorIndex = i;

      if (vuStates[i].vuUp) {
        
        vuStates[i].vuSize += 8;
        
        matrix.fillRect(x, VU_H - vuStates[i].vuSize, VU_W, vuStates[i].vuSize, palette->colors[colorIndex]);
        
        if (vuStates[i].vuSize >= VU_H) {
          vuStates[i].vuUp = false;
        }
      } else if (vuStates[i].vuUp == false && vuStates[i].vuSize >= 0) {
        
        matrix.fillRect(x, VU_H - vuStates[i].vuSize, VU_W, 1, CLEAR);
        vuStates[i].vuSize -= 0.75;
        
      }
    }
  }

private: 

  Palette* palette;

  VuState vuStates[VU_COUNT];

};

#endif //QUAD_VU_H
