
#ifndef BIG_VU_H
#define BIG_VU_H

#include "Scene.h"

class BigVu : public TickerScene {
  
public:
  BigVu(color_t color, byte note, byte noteCount = 1, bool isHorizontal = true) : color(color), note(note), noteCount(noteCount), isHorizontal(isHorizontal) {
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
      
      byte vuH, vuW, x, y;

      VuState* state = &vuStates[i];

      if (state->vuUp) {
        state->vuSize += isHorizontal ? 16 : 8;
      }

      if (isHorizontal) {
        x = isOtherDisplay ? (displayHalfW - state->vuSize) : (state->vuUp ? 0 : state->vuSize);
        y = i*vuH;

        vuW = state->vuUp ? state->vuSize : 2;
        vuH = displayH/noteCount;

      } else {
        vuW = (displayW/2)/noteCount;

        x = isOtherDisplay ? (displayW/2 - ((i+1) * vuW)) : i * vuW;
        y = displayH - vuStates[i].vuSize;

        vuH = state->vuUp ? vuStates[i].vuSize : 1;
      }

      if (state->vuUp) {
        
        matrix.fillRect(x, y, vuW, vuH, color);
        
        if (state->vuSize >= (isHorizontal ? displayHalfW : displayH)) {
          state->vuUp = false;
        }

      } else if (state->vuUp == false && state->vuSize >= 0) {
        
        matrix.fillRect(x, y, vuW, vuH, CLEAR);
        state->vuSize = state->vuSize - (isHorizontal ? 2 : 0.75f);
      }
    }
  }

private: 
  color_t color;

  VuState vuStates[4];
  
  byte note;
  byte noteCount = 1;
  bool isHorizontal;

};

#endif //BIG_VU_H
