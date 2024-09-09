
#ifndef FLASHING_SIGN_H
#define FLASHING_SIGN_H

#include "MessageScene.h"

class FlashingSign : public MessageScene {
public:
  enum TextCollection {
    friendship = 0,
    brighter,
    version
  };
  
  public:
  FlashingSign(Palette* palette, 
               TextCollection textCollection,
               byte contourSize = 3)
               
  : MessageScene(palette), contourSize(contourSize), textCollection(textCollection) {

    if (textCollection == friendship) {
      textCount = 3;
    }

    colorCount = palette->size;
  }

  virtual void midiNote(byte noteValue) override {
    if (textCount > 1) {
      textIndex = noteValue % textCount;


      needClear = true;
    }
  }

  virtual void draw() override {

    if (needClear) {
      clearScreen();
      needClear = false;
    }
    
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(palette->colors[colorIndex]);

    String toDraw;

    switch (textCollection) {
      case friendship : {
        switch (textIndex) {
          case 0 : toDraw = F("FRIENDSHIP"); break;
          case 1 : toDraw = F("&"); break;
          default : toDraw = F("BRAVERY"); break;
        }
      } break;
      case brighter : toDraw = F("BRIGHTER"); break;
      default : toDraw = F("v1.1.0"); break;
    }

    drawCentreString(toDraw, 0, 0);

    byte xOffset = isOtherDisplay ? displayW/2 : 0;

    for (byte i = 0; i < contourSize; i++) {
      byte cIndex = (colorIndex + 1 + i) % colorCount;
      matrix.drawRect(i - xOffset,i, displayW - i*2, displayH - i*2, palette->colors[cIndex]);
    }
    
  }

  protected:
  byte textCount = 1;
  bool needClear = false; 
  TextCollection textCollection;
  byte contourSize;
  byte textIndex = 0;
};

#endif //FLASHING_SIGN_H
