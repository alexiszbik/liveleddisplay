
#ifndef BIG_VU_H
#define BIG_VU_H

#include "Scene.h"

#define VU_W 32

class BigVu : public TickerScene {
  
public:
  BigVu(color_t color, byte note, byte noteCount = 1) : color(color), note(note), noteCount(noteCount) {
  }

  virtual ~BigVu() {
  }
  
public:
  virtual void midiNote(byte noteValue) override {

    if (noteValue >= note && noteValue < (note + noteCount))
    {
      byte vuIndex = noteValue - note;
      vuStates[vuIndex].reset();
    }
  }

  virtual void draw() override {
    
    for (byte i = 0; i < noteCount; i++) {
      
      byte vuH = displayH/noteCount;
      byte y = i*vuH;

      VuState* state = &vuStates[i];
  
      if (state->vuUp) {
        
        state->vuSize += 16;
  
        byte x = isOtherDisplay ? (VU_W - state->vuSize) : 0;
        
        matrix.fillRect(x, y, state->vuSize, vuH, color);
        
        if (state->vuSize >= VU_W) {
          state->vuUp = false;
        }
      } else if (state->vuUp == false && state->vuSize >= 0) {
  
        byte x = isOtherDisplay ? (VU_W - state->vuSize) : state->vuSize;
        
        matrix.fillRect(x, y, 2, vuH, CLEAR);
        state->vuSize = state->vuSize - 2;
      }
    }
  }

private: 

  color_t color;

  VuState vuStates[2];
  
  byte note;
  byte noteCount = 1;

};

#endif //BIG_VU_H
