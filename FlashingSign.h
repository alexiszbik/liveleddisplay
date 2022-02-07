
#ifndef FLASHING_SIGN_H
#define FLASHING_SIGN_H

#include "Palette.h"

#define WORD F("BRIGHTER")

class FlashingSign : public Scene {
  
  public:
  FlashingSign(Palette* palette) : palette(palette) {
    colorCount = palette->size;
  }

  virtual ~FlashingSign() {
     delete palette;
  }

  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;

      colorIndex = (colorIndex + 1) % colorCount;
      
    }
  }

  void drawCentreString() {
    byte xOffset = isOtherDisplay ? displayW/2 : 0;
    
    matrix.setCursor(0, 0);
    int16_t x1, y1;
    uint16_t w, h;
    matrix.getTextBounds(WORD, 0, 0, &x1, &y1, &w, &h);
    matrix.setCursor(displayW/2 - w/2 - xOffset, displayH/2 - h/2);
    matrix.print(WORD);
  }


  virtual void draw() override {
    
    matrix.setTextSize(1);
    matrix.setTextColor(palette->colors[colorIndex]);
    matrix.setTextWrap(false);
    drawCentreString();

    byte xOffset = isOtherDisplay ? displayW/2 : 0;

    for (byte i = 0; i < 3; i++) {
      byte cIndex = (colorIndex + 1 + i) % colorCount;
      matrix.drawRect(i - xOffset,i, displayW - i*2, displayH - i*2, palette->colors[cIndex]);
    }
    
  }

  protected:
  byte colorCount;  
  byte colorIndex = 0; 
  
  Palette* palette;
};

#endif //FLASHING_SIGN_H
