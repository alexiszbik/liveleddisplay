
#ifndef BIG_VU_H
#define BIG_VU_H

#include "Scene.h"
#include "Ticker.h"

#define VU_H 16
#define VU_W 32

class BigVu : public Scene {
  
public:
  BigVu(Palette* palette) : palette(palette)  {
  }

  virtual ~BigVu() {
    delete ticker;
  }
  
public:
  virtual void midiNote(byte noteValue) override {
    
    if (noteValue == 60) {
      vuSize = 0;
      vuUp = true;
    }
    
  }

  virtual void showFrame(bool _isOtherDisplay) {
      Scene::showFrame(_isOtherDisplay);
      
      if (ticker->checkTime()) {
        needRefresh = true;
      }
  }

  virtual void draw() override {

    if (vuUp) {
      
      vuSize += 16;

      byte x = isOtherDisplay ? (VU_W - vuSize) : 0;
      
      matrix.fillRect(x, 0, vuSize, VU_H, palette->colors[0]);
      
      if (vuSize >= VU_W) {
        vuUp = false;
      }
    } else if (vuUp == false && vuSize >= 0) {

      byte x = isOtherDisplay ? (VU_W - vuSize) : vuSize;
      
      matrix.fillRect(x, 0, 2, VU_H, CLEAR);
      vuSize = vuSize - 2;
    }
  }

private: 

  Palette* palette;
  Ticker *ticker = new Ticker(20);

  float vuSize = 0;
  bool vuUp = false;

};

#endif //BIG_VU_H
