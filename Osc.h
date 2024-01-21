
#ifndef OSC_H
#define OSC_H

#include "Scene.h"

#define NO_VALUE 100

#define START_NOTE 48

#define NOTE_ON_OFF 60

#define VU_H 16
#define VU_W 16

class WaveData {
  public:
  byte buf = 0;
  byte offset = 0;
  byte speed = 1;

  void updateOffset() {
    offset = (offset + speed) % displayW; 
  }
};

class Osc : public Scene {
  
public:
  Osc(Palette* palette) : palette(palette) {
    waveCount = palette->size;
    waveData = new WaveData[waveCount];
    for (byte w = 0; w < waveCount; w++) {
      waveData[w].speed = (w+1);
    }
  }

  virtual ~Osc() {
      delete palette;
      delete[] waveData;
  }
  
public:
  virtual void tick(bool state) override {
    if (state && !squareMode)  {
      setNeedsRefresh();
      for (byte w = 0; w < waveCount; w++) {
        waveData[w].updateOffset();
      } 
    }
  }

  virtual void midiNote(byte noteValue) override {

    if (noteValue >= START_NOTE && noteValue <= (START_NOTE + 3))
    {
      if (!squareMode) {
        needsClear = true;
      }
      squareMode = true;
      squarePosition = noteValue - START_NOTE;
    } 
    else if (noteValue == NOTE_ON_OFF) {
      needsClear = true;
      showOsc = false;
      
    } else {
      if (squareMode) {
        needsClear = true;
      }
      squareMode = false;
      showOsc = true;
    }
    setNeedsRefresh();
  }

  virtual void draw() override {

    if (needsClear) {
      clearScreen();
      needsClear = false;
    }

    if (squareMode) {
      if (xSqr >= 0) {
        matrix.fillRect(xSqr, 0, VU_W, VU_H, COLOR(0,0,0));
      }

      byte colorIndex = getRandom() % palette->size;
      color_t c = palette->colors[colorIndex];

      xSqr = isOtherDisplay ? (((int)squarePosition - 2) * (int)VU_W) : (int)squarePosition * (int)VU_W;
      
      if (xSqr >= 0) {
        matrix.fillRect(xSqr, 0, VU_W, VU_H, c);
      }
      
      
    } else if (showOsc) {
      const byte w = displayHalfW;

      for (byte i = 0; i < w; i++) {
        
        for (byte s = 0; s < waveCount; s++) {

          byte waveOffset = (displayW/waveCount) * s;
          
          float x = ((float)(i + waveData[s].offset + waveOffset + (isOtherDisplay ? displayHalfW : 0)))/(float)w;
          float y = cos(PI*x) * displayHalfH + displayHalfH; 
          y = fmin(y,displayH - 1);

          float off_x = -((float)waveData[s].speed)/(float)w;
          float prevy = cos(PI*(x+off_x)) * displayHalfH + displayHalfH; 
          prevy = fmin(prevy,displayH - 1);

          matrix.drawPixel(i, prevy, COLOR(0,0,0));
          waveData[s].buf = y;
        }

        for (byte s = 0; s < waveCount; s++) {
          color_t c = palette->colors[s];
          matrix.drawPixel(i,  waveData[s].buf, c);
        }
      }
    }
  }

private:
  byte waveCount = 0;
  Palette* palette;

  bool squareMode = false;
  bool needsClear = false;
  byte squarePosition = 0;

  bool showOsc = true;

  WaveData* waveData = NULL;

  int xSqr = 0;
};


#endif //OSC_H
