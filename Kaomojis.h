
#ifndef KAOMOJIS_H
#define KAOMOJIS_H

#include "Palette.h"
#include "Scene.h"

class Kaomojis : public Scene {
  
  public:
  Kaomojis(Palette* palette) : palette(palette) {
    colorCount = palette->size;
  }

  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;

      colorIndex = (colorIndex + 1) % colorCount;
      
    }
  }

  void drawCentreString(const String &buf) {
    byte xOffset = isOtherDisplay ? displayW/2 : 0;
    
    matrix.setCursor(0, 0);
    int16_t x1, y1;
    uint16_t w, h;
    matrix.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);
    matrix.setCursor(displayW/2 - w/2 - xOffset, displayH/2 - h/2 + 1);
    matrix.print(buf);
  }


  virtual void draw() override {
    clearScreen();
    matrix.setTextSize(2);
    matrix.setTextColor(palette->colors[colorIndex]);
    matrix.setTextWrap(false);
    byte randomStringIndex = random(1000) % 10;
    //drawCentreString(text[randomStringIndex]);
    
  }

  protected:
  byte colorCount;  
  byte colorIndex = 0; 
  
  Palette* palette;
  String text[10] = {"(*^o^)", "(>m<)", "(*'o'*)", "=^..^=", "(;-_-)", "(o_O)", "(>_<~)", "(T^T)", "(^_^*)", "U=x=U" } ;
  
};

#endif //KAOMOJIS_H
