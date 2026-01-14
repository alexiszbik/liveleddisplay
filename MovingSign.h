
#ifndef MOVING_SIGN_H
#define MOVING_SIGN_H

#include "MessageScene.h"

class MovingSign : public SyncScene {
public:
  enum TextCollection {
    fantasy = 0,
    delaurentis = 1,
    ymnk,
    douran,
  };

public:
  MovingSign(Palette* palette,
             TextCollection textCollection,
             bool yMove = false,
             bool midiSync = true)

    : palette(palette), textCollection(textCollection), yMove(yMove) {

    colorCount = palette->size;

    switch (textCollection) {
      case fantasy: toDraw = F("FANTASY!"); break;
      case delaurentis: toDraw = F("DeLaurentis"); break;
      case ymnk: toDraw = F("YMNK"); break;
      case douran: toDraw = F("Douran"); break;
      //case fantasy : toDraw = F("そばにきてくらい"); break;
      default: toDraw = F("v1.2.0"); break;
    }

    setSynced(midiSync);

    matrix.setTextSize(2);
    matrix.setTextWrap(false);

    int16_t x1, y1;
    uint16_t w, h;
    matrix.getTextBounds(toDraw, 0, 0, &x1, &y1, &w, &h);

    textWidth = w;
  }

  virtual void midiSync() override {
    if (synced) {
      updateOffsets();
      setNeedsRefresh();
    }
  }

  virtual void tick(bool state) override {
    if (!synced && state) {
      updateOffsets();
      setNeedsRefresh();
    }
  }

  virtual void updateOffsets() {
    xOffset = (xOffset + 1) % textWidth;
    yOffset = (yOffset + 1) % displayH;
  }

  void drawText(int offset) {
    byte len = toDraw.length();
    const byte letterSize = 12;
    for (byte c = 0; c < len; c++) {
      char letter = toDraw.charAt(c);
      matrix.setTextColor(palette->colors[c % colorCount]);
      int y = 1;
      if (yMove) {
        y += yOffset * ((c % 2) ? 1 : -1);
        for (int h = -1; h <= 1; h++) {
          matrix.setCursor(offset + c * letterSize, y + h * displayH);
          matrix.print(letter);
        }
      } else {
        matrix.setCursor(offset + c * letterSize, y);
        matrix.print(letter);
      }
    }
  }

  virtual void draw() override {

    clearScreen();

    for (byte i = 0; i < 2; i++) {
      drawText(-xOffset + i * textWidth);
    }
  }

protected:
  String toDraw;
  TextCollection textCollection;
  byte colorCount;
  byte colorIndex = 0;
  byte xOffset = 0;
  byte yOffset = 0;
  byte textWidth = 0;
  bool yMove = false;

  Palette* palette = nullptr;
};

#endif  //MOVING_SIGN_H
