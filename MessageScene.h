
#ifndef MESSAGE_SCENE_H
#define MESSAGE_SCENE_H

#include "Palette.h"
#include "Scene.h"


class MessageScene : public AutoRefreshedScene {
  
  public:
  MessageScene(Palette* palette) : palette(palette) {
    colorCount = palette->size;
  }

  virtual ~MessageScene() {
     delete palette;
  }

  virtual void updateOffsets() override {
      colorIndex = (colorIndex + 1) % colorCount;
  }

  void drawCentreString(const String &buf, byte xOffset = 0, byte yOffset = 1) {    
    initCursor();
    int16_t x1, y1;
    uint16_t w, h;
    matrix.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);
    matrix.setCursor(displayW/2 - w/2 + xOffset, displayH/2 - h/2 + yOffset);
    matrix.print(buf);
  }

  protected:
  byte colorCount;  
  byte colorIndex = 0; 
  
  Palette* palette = nullptr;
  
  
};

#endif //MESSAGE_SCENE_H
