
#ifndef HEARTH_H
#define HEARTH_H

#include "Scene.h"

class Hearth : public Scene {

public:

  Hearth(Palette* palette) : palette(palette) {
  }
  virtual ~Hearth() {
    delete palette;
  }

  public:
  virtual void tick(bool state) override {
    if (state)  {
      setNeedsRefresh();

      offset = (offset + 1) % 16;
    }
  }
  
  
  virtual void draw() override {
    clearScreen();
      //We make our hearths here because of weird memory allocation
      matrix.startWrite();

      //top
      byte maxW = 16;
      byte hWide = 14;

      for (int i = -1; i < 4; i++) {
        int hX = (maxW - hWide) / 2;
        hX = hX + maxW*i + offset;

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
  }

private:
    Palette* palette;
    byte offset = 0;

};

#endif //HEARTH_H
