
#ifndef VU_METER_H
#define VU_METER_H

#include "Scene.h"
#include "Ticker.h"

#define VU_H 16
#define VU_W 16

class VuMeter : public Scene {
  
public:
  VuMeter(Palette* palette) : palette(palette)  {
  }
  
public:
  virtual void midiNote(byte noteValue) override {
    if (noteValue == (isOtherDisplay ? 62 : 60)) {
      vuSize[0] = 0;
      vuUp[0] = true;
      
    } else if (noteValue == (isOtherDisplay ? 63 : 61)) {
      vuSize[1] = 0;
      vuUp[1] = true;
    }
      
  }

  virtual void showFrame(bool _isOtherDisplay) {
      Scene::showFrame(_isOtherDisplay);
      
      if (ticker->checkTime()) {
        needRefresh = true;
      }
  }

  virtual void draw() override {

    for (byte i = 0; i < 2; i++) {
      byte x = i * displayW/2/2;

      byte colorIndex = i + (isOtherDisplay ? 2 : 0);

      if (vuUp[i]) {
        
        vuSize[i] = vuSize[i] + 8;
        
        matrix.fillRect(x, VU_H - vuSize[i], VU_W, vuSize[i], palette->colors[colorIndex]);
        
        if (vuSize[i] >= VU_H) {
          vuUp[i] = false;
        }
      } else if (vuUp[i] == false && vuSize[i] >= 0) {
        matrix.fillRect(x, VU_H - vuSize[i], VU_W, 1, CLEAR);
        vuSize[i] = vuSize[i] - 0.75;
      }
    }

  }


private:
  Palette* palette;
  Ticker *ticker = new Ticker(20);

  float vuSize[2] = {0, 0};
  bool vuUp[2] = {false, false};

};

#endif //BIG_YMNK_H
