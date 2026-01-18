
#ifndef FLASHING_SIGN_H
#define FLASHING_SIGN_H

#include "MessageScene.h"

class FlashingSign : public MessageScene {
public:
  enum TextCollection {
    friendship = 0,
    brighter,
    version,
    deadChic,
    vss,
    elvett,
    sonia,
    ilEstVilaine
  };

public:
  FlashingSign(Palette* palette,
               TextCollection textCollection,
               byte contourSize = 3,
               bool autoChange = false)

    : MessageScene(palette), contourSize(contourSize), textCollection(textCollection), autoChange(autoChange) {

    if (textCollection == friendship || textCollection == vss || textCollection == ilEstVilaine) {
      textCount = 3;
    }

    colorCount = palette->size;
  }

  virtual void midiNote(byte noteValue) override {
    if (autoChange) {
      return;
    }
    if (textCount > 1) {
      textIndex = noteValue % textCount;

      needClear = true;
    }
  }

  virtual void updateOffsets() override {
    MessageScene::updateOffsets();
    if (autoChange) {
      autoChangeCount++;
      if (autoChangeCount >= 8) {
        if (textCount > 1) {
          textIndex = (textIndex + 1) % textCount;

          needClear = true;
        }
        autoChangeCount = 0;
      }
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
      case friendship:
        {
          switch (textIndex) {
            case 0: toDraw = F("FRIENDSHIP"); break;
            case 1: toDraw = F("&"); break;
            default: toDraw = F("BRAVERY"); break;
          }
        }
        break;
      case brighter: toDraw = F("BRIGHTER"); break;
      case deadChic: toDraw = F("Dead Chic"); break;
      case vss:
        {
          switch (textIndex) {
            case 0: toDraw = F("VIPERES"); break;
            case 1: toDraw = F("SUCREES"); break;
            default: toDraw = F("SALEES"); break;
          }
        }
        break;
      case elvett: toDraw = F("ELVETT"); break;
      case sonia: toDraw = F("SON'IA 360"); break;
      case ilEstVilaine:
        {
          switch (textIndex) {
            case 0: toDraw = F("Il"); break;
            case 1: toDraw = F("Est"); break;
            default: toDraw = F("Vilaine"); break;
          }
        }
        break;
      default: toDraw = F("v1.2.1"); break;
    }

    drawCentreString(toDraw, 0, 0);

    if (palette) {
      for (byte i = 0; i < contourSize; i++) {
        byte cIndex = (colorIndex + 1 + i) % colorCount;
        matrix.drawRect(i, i, displayW - i * 2, displayH - i * 2, palette->colors[cIndex]);
      }
    }
  }

protected:
  byte textCount = 1;
  bool needClear = false;
  TextCollection textCollection;
  byte contourSize;
  byte textIndex = 0;
  bool autoChange = false;
  byte autoChangeCount = 0;
};

#endif  //FLASHING_SIGN_H
