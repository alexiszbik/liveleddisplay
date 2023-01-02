
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
    
    if (noteValue == note) {
      vuSize[0] = 0;
      vuUp[0] = true;
    }
    if (noteCount == 2) {
      if (noteValue == (note + 1)) {
        vuSize[1] = 0;
        vuUp[1] = true;
      }
    }
  }

  virtual void showFrame(bool _isOtherDisplay) {
      Scene::showFrame(_isOtherDisplay);
      
      if (ticker->checkTime()) {
        needRefresh = true;
      }
  }

  virtual void draw() override {
    
    for (byte i = 0; i < noteCount; i++) {
      
      byte vuH = displayH/noteCount;
      byte y = i*vuH;
  
      if (vuUp[i]) {
        
        vuSize[i] += 16;
  
        byte x = isOtherDisplay ? (VU_W - vuSize[i]) : 0;
        
        matrix.fillRect(x, y, vuSize[i], vuH, color);
        
        if (vuSize[i] >= VU_W) {
          vuUp[i] = false;
        }
      } else if (vuUp[i] == false && vuSize[i] >= 0) {
  
        byte x = isOtherDisplay ? (VU_W - vuSize[i]) : vuSize[i];
        
        matrix.fillRect(x, y, 2, vuH, CLEAR);
        vuSize[i] = vuSize[i] - 2;
      }
    }
  }

private: 

  color_t color;

  float vuSize[2] = {0, 0};
  bool vuUp[2] = {false, false};
  byte note;
  byte noteCount = 1;

};

#endif //BIG_VU_H
