
#ifndef BIG_YMNK_H
#define BIG_YMNK_H

#include "Scene.h"


class BigYMNK : public Scene {
  
public:
  BigYMNK(Palette* palette) : palette(palette)  {

  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;
      colorIndex = (colorIndex + 1) % palette->size;
    }
  }


  virtual void draw() override {

    matrix.setTextSize(2);
    matrix.setTextWrap(false);

    byte cIndex = (colorIndex + (isOtherDisplay ? 2 : 0)) % palette->size;

    matrix.setTextColor(palette->colors[cIndex]);
    matrix.setCursor(3,1);
    matrix.print(isOtherDisplay ? "N" : "Y");

    cIndex = (cIndex + 1) % palette->size;


    matrix.setTextColor(palette->colors[cIndex]);
    matrix.setCursor(19,1);
    matrix.print(isOtherDisplay ? "K" : "M");
  }


private:
  Palette* palette;
  byte colorIndex;
};

#endif //BIG_YMNK_H
