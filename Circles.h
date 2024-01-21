
#ifndef CIRCLES_H
#define CIRCLES_H

#include "Scene.h"
#include "Palette.h"

#define C_SIZE 12

class Circles : public Scene {

public:

  Circles(Palette* palette, bool hTest = false) : palette(palette), hTest(hTest) {
  }
  virtual ~Circles() {
    delete palette;
  }

public:
  virtual void tick(bool state) override {
    if (state)  {
      setNeedsRefresh();

      offset = (offset + 1) % C_SIZE;
      hOffset = (hOffset + 1) % 16;
    }
  }

  virtual void draw() override {
    if (hTest) {
      clearScreen();
      //We make our hearths here because of weird memory allocation
      matrix.startWrite();

      //top
      byte maxW = 16;
      byte hWide = 14;

      for (int i = -1; i < 2; i++) {
        int hX = (maxW - hWide) / 2;
        hX = hX + maxW*i + hOffset;

        matrix.drawLine(hX+2, 2, hX+4, 2, palette->colors[0]);
        matrix.drawLine(hX+9, 2, hX+11, 2, palette->colors[0]);

        matrix.drawLine(hX+5, 3, hX+6, 4, palette->colors[0]);
        matrix.drawLine(hX+7, 4, hX+8, 3, palette->colors[0]);

        matrix.drawPixel(hX+1, 3, palette->colors[0]);
        matrix.drawPixel(hX+(hWide-2), 3, palette->colors[0]);

        matrix.drawLine(hX, 4, hX, 7, palette->colors[0]);
        matrix.drawLine(hX+(hWide-1), 4, hX+(hWide-1), 7, palette->colors[0]);

        matrix.drawLine(hX+1, 8, hX+6, 13, palette->colors[0]);
        matrix.drawLine(hX+7, 13, hX+(hWide-2), 8, palette->colors[0]);
      }

      matrix.endWrite();

    } else {
      for (byte i = 0; i < palette->size; i++) {
        int idx = (offset - i);
        byte r = (idx + C_SIZE) % C_SIZE;
        byte x = isOtherDisplay ? 0 : displayHalfW;
        matrix.drawCircle(x, displayHalfH, r * 4, palette->colors[i]);
      }
    }
  }

private:
  Palette* palette;

  bool hTest;
  byte offset = 0;
  byte hOffset = 0;

};

#endif //CIRCLES_H
