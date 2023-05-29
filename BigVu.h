
#ifndef BIG_VU_H
#define BIG_VU_H

#include "Scene.h"

class BigVu : public TickerScene {
public:
enum Mode {
  horizontal = 0,
  verticalMirrored,
  verticalWide
};
  
public:
  BigVu(Palette* palette, byte note, byte noteCount = 1, Mode mode = horizontal) 
  : palette(palette), note(note), noteCount(noteCount), mode(mode) {
  }

  virtual ~BigVu() {
    delete palette;
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

      bool isHorizontal = (mode == horizontal);

      color_t color = palette->colors[i % palette->size];

      VuState* state = &vuStates[i];

      if (state->vuUp) {
        state->vuSize += getRiseAmount();
      }

      switch(mode) {
        case horizontal : {
          x = isOtherDisplay ? (displayHalfW - state->vuSize) : (state->vuUp ? 0 : state->vuSize);
          y = i*vuH;

          vuW = state->vuUp ? state->vuSize : 2;
          vuH = displayH/noteCount;
        }
        break;
        case verticalMirrored : {
          vuW = displayHalfW/noteCount;

          x = isOtherDisplay ? (displayHalfW - ((i+1) * vuW)) : i * vuW;
          y = displayH - vuStates[i].vuSize;

          vuH = state->vuUp ? vuStates[i].vuSize : 1;
        }
        break;
        case verticalWide : {
          vuW = displayHalfW/2;

          if (isOtherDisplay == false && i >= 2) {
            continue;
          } else if (isOtherDisplay && i < 2) {
            continue;
          }

          x = (i * vuW) - (isOtherDisplay ? displayHalfW : 0);
          y = displayH - vuStates[i].vuSize;

          vuH = state->vuUp ? vuStates[i].vuSize : 1;
        }
        break;
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

  virtual float getRiseAmount() {
    return mode == horizontal ? 16 : 8;
  }

protected:
  VuState vuStates[8];
  byte noteCount;

private: 
  Palette* palette;
  byte note;
  Mode mode;
  
};


#endif //BIG_VU_H
