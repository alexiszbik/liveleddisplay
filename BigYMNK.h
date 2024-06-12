
#ifndef BIG_YMNK_H
#define BIG_YMNK_H

#include "Scene.h"


class BigYMNK : public AutoRefreshedScene {
  
public:
  BigYMNK(Palette* palette, bool inverted = false) : palette(palette), inverted(inverted)  {
  }

  virtual ~BigYMNK() {
     delete palette;
  }
  
public:
  virtual void updateOffsets() override {
      colorIndex = (colorIndex + 1) % palette->size;
  }


  virtual void draw() override {

    matrix.setTextSize(2);

    if (inverted) {
      if (!once) {
        matrix.fillScreen(COLOR(0,0,7));

        matrix.setTextColor(COLOR(0,0,0));
        matrix.setCursor(3,1);
        matrix.print(isOtherDisplay ? F("N") : F("Y"));

        matrix.setCursor(19,1);
        matrix.print(isOtherDisplay ? F("K") : F("M")); 

        once = true;
      }
    } else {
      byte cIndex = (colorIndex + (isOtherDisplay ? 2 : 0)) % palette->size;

      matrix.setTextColor(palette->colors[cIndex]);
      matrix.setCursor(3,1);
      matrix.print(isOtherDisplay ? F("N") : F("Y"));

      cIndex = (cIndex + 1) % palette->size;

      matrix.setTextColor(palette->colors[cIndex]);
      matrix.setCursor(19,1);
      matrix.print(isOtherDisplay ? F("K") : F("M"));
    }
  }


private:
  Palette* palette;
  byte colorIndex = 0;
  bool inverted = false;
  bool once = false;
};

#endif //BIG_YMNK_H
