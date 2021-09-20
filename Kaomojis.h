
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
    String toDraw;

    switch (randomStringIndex) {
      case 0 : toDraw = F("(*^o^)"); break;
      case 1 : toDraw = F("(>m<)"); break;
      case 2 : toDraw = F("(*'o'*)"); break;
      case 3 : toDraw = F("=^..^="); break;
      case 4 : toDraw = F("(;-_-)"); break;
      case 5 : toDraw = F("(o_O)"); break;
      case 6 : toDraw = F("(>_<~)"); break;
      case 7 : toDraw = F("(T^T)"); break;
      case 8 : toDraw = F("(^_^*)"); break;
      default : toDraw = F("U=x=U"); break;
    }

    
    drawCentreString(toDraw);

    //strcpy_P(buffer, (char *)pgm_read_word(&(string_table[0])));
    //drawCentreString(buffer);
    //matrix.print(buffer);
  }

  protected:
  byte colorCount;  
  byte colorIndex = 0; 
  
  Palette* palette;
  
  
};

#endif //KAOMOJIS_H
