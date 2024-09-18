
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


  void writeLetter(int index) {
    switch (index) {
        case 0 :
            matrix.setCursor(3,1);
            matrix.print(F("Y"));
        break;
        case 1 :
            matrix.setCursor(19,1);
            matrix.print(F("M"));
        break;
        case 2 :
            matrix.setCursor(35,1);
            matrix.print(F("N"));
        break;
        case 3 :
            matrix.setCursor(51,1);
            matrix.print(F("K"));
        break;
        default : break;
    }
  }

  virtual void draw() override {

    matrix.setTextSize(2);

    if (inverted) {
      if (!once) { ///yup this is not working with START/STOP
        matrix.fillScreen(COLOR(0,0,7));

        matrix.setTextColor(COLOR(0,0,0));
        for (byte i = 0; i < 4; i++) {
             writeLetter(i);
        }
        once = true;
      }
    } else {
        for (byte i = 0; i < 4; i++) {
            byte cIndex = (colorIndex + i)  % palette->size;

            matrix.setTextColor(palette->colors[cIndex]);
            writeLetter(i);
        }
    }
  }


private:
  Palette* palette;
  byte colorIndex = 0;
  bool inverted = false;
  bool once = false;
};

#endif //BIG_YMNK_H
