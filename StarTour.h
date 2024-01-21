
#ifndef STARTOUR_H
#define STARTOUR_H

#include "Scene.h"
#include "Palette.h"

#define TRAIL_COUNT 6

class StarTour : public AutoRefreshedScene {
  struct TrailData {
    byte len;
    byte offset;

    void increment() {
      offset = (offset + 1) % len;
    }
  };
  
public:
  StarTour() {
    for (byte i = 0; i < TRAIL_COUNT; i++) {
      byte len = 8 + random(10);
      trailData[i].len = len;
      trailData[i].offset = 0;
    }
  }

  virtual ~StarTour() {
  }
  
  
public:
  virtual void updateOffsets() override {
      for (byte i = 0; i < TRAIL_COUNT; i++) {
        trailData[i].increment();
      }
  }

  color_t grey(byte level) {
    return matrix.Color333(level, level, level);
  }

  virtual void draw() override {

    matrix.startWrite();

    byte midY = displayH/2;
    float yIncrement = ((float)midY)/((float)width);

    float y = 0.f;
    for (byte x = 0; x < width; x++) {
      y = y + yIncrement;

      const byte z = TRAIL_COUNT/2;
  
      for (int b = 0; b < z; b++) {
        static float ratio[z] = {0.5f,1.5f,4};
        float dy = y * ratio[b];
        
        byte db = b*2;
        TrailData* d = &trailData[db];
        byte colorIndex = ((x + d->offset) % d->len);
        color_t c = (colorIndex <= 7) ? grey(colorIndex) : clearColor();
        matrix.writePixel(!isOtherDisplay ? width - x : x, midY + floor(dy),c);
        
        db = db + 1;
        d = &trailData[db];
        colorIndex = ((x + d->offset) % d->len);
        c = (colorIndex <= 7) ? grey(colorIndex) : clearColor();
        matrix.writePixel(!isOtherDisplay ? width - x : x, midY - 1 - floor(dy),c);
      }
    }
    
    matrix.endWrite();
  }


public:
  byte offset = 0;
  const byte width = displayW/2;
  
  TrailData trailData[TRAIL_COUNT];

};

#endif //STARTOUR_H
