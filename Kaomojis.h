
#ifndef KAOMOJIS_H
#define KAOMOJIS_H

#include "MessageScene.h"


class Kaomojis : public MessageScene {
  
  public:
  Kaomojis(Palette* palette) : MessageScene(palette) {
  }

  virtual void draw() override {
    clearScreen();
    matrix.setTextSize(2);
    matrix.setTextColor(palette->colors[colorIndex]);
    
    byte randomStringIndex = getRandom() % 6;//10;
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
  }
  
  
};

#endif //KAOMOJIS_H
