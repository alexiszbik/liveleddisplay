
#ifndef FLASHING_SIGN_H
#define FLASHING_SIGN_H

#include "MessageScene.h"

class FlashingSign : public MessageScene {
  
  public:
  FlashingSign(Palette* palette, 
               const char * const *  texts,
               byte textCount,
               byte contourSize = 3)
               
  : MessageScene(palette), contourSize(contourSize), textCount(textCount), texts(texts) {

    strcpy_P(txtbuf, (char *)pgm_read_word(&(texts[0])));
    colorCount = palette->size;
  }

  virtual void midiNote(byte noteValue) override {
    if (textCount > 1) {
      textIndex = noteValue % textCount;
      strcpy_P(txtbuf, (char *)pgm_read_word(&(texts[textIndex])));
      needClear = true;
    }
  }

  void drawString() {
    byte xOffset = isOtherDisplay ? displayW/2 : 0;
    
    matrix.setCursor(0, 0);
    int16_t x1, y1;
    uint16_t w, h;
    matrix.getTextBounds(txtbuf, 0, 0, &x1, &y1, &w, &h);
    matrix.setCursor(displayW/2 - w/2 - xOffset, displayH/2 - h/2);
    matrix.print(txtbuf);
  }


  virtual void draw() override {

    if (needClear) {
      clearScreen();
      needClear = false;
    }
    
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(palette->colors[colorIndex]);
    drawString();

    byte xOffset = isOtherDisplay ? displayW/2 : 0;

    for (byte i = 0; i < contourSize; i++) {
      byte cIndex = (colorIndex + 1 + i) % colorCount;
      matrix.drawRect(i - xOffset,i, displayW - i*2, displayH - i*2, palette->colors[cIndex]);
    }
    
  }

  protected:
  bool needClear = false; 

  const char * const *  texts;

  char txtbuf[30];
  byte textCount;
  byte contourSize;
  byte textIndex = 0;
};

#endif //FLASHING_SIGN_H
