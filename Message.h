
#ifndef MESSAGE_H
#define MESSAGE_H

#include "Palette.h"

class Message : public Scene {
  
  public:
  Message(String text, Palette* palette) : text(text), palette(palette) {
    colorCount = palette->size;
  }

  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;

      colorIndex = (colorIndex + 1) % colorCount;

      pos = (pos + 1) % lineTotal;
      
    }
  }

  void drawCentreString(const String &buf) {
    byte xOffset = isOtherDisplay ? displayW/2 : 0;
    
    matrix.setCursor(0, 0);
    int16_t x1, y1;
    uint16_t w, h;
    matrix.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);
    matrix.setCursor(displayW/2 - w/2 - xOffset, displayH/2 - h/2);
    matrix.print(buf);
  }


  virtual void draw() override {
    /*
    matrix.setTextSize(1);
    matrix.setTextColor(palette->colors[colorIndex]);
    matrix.setTextWrap(false);
    drawCentreString(text);
    */

    matrix.startWrite();

    /*
    int x = -pos;
    
    while (x < width) {
      matrix.writeFastHLine(x, 0, lineW, color);
      x += lineW;
      matrix.writeFastHLine(x, 0, lineP, CLEAR);
      x += lineP;
    }

    int y = pos - lineTotal - 3;
    
    while (y < displayH) {
      matrix.writeFastVLine(0, y, lineW, color);
      y += lineW;
      matrix.writeFastVLine(0, y, lineP, CLEAR);
      y += lineP;
    }
    */

    byte l = pos;

    byte total = width*2 + height*2 - 4;

    bool fill = true;

    int i = 0;
    int xPos = 0;
    int yPos = 0;

    int xIt = 1;
    int yIt = 0;
    
    while (i < total) {

      if (l >= lineW + lineP) {
        fill = true;
        l = 0;
      }
      else if (l >= lineW) {
        fill = false;
      }

      color_t color = fill ? palette->colors[0] : CLEAR;

      if (i == width) {
        xPos = width - 1;
        yPos = 1; 

        xIt = 0;
        yIt = 1;
      } else if (i == (width + height - 2)) {
        xPos = width - 1;
        yPos = displayH - 1; 

        xIt = -1;
        yIt = 0;
      } else if (i == (width + height + width - 2)) {
        xPos = 0;
        yPos = height - 2; 

        xIt = 0;
        yIt = -1;
      }
      
      matrix.drawPixel(xPos, yPos, color);
        
      xPos = xPos + xIt;
      yPos = yPos + yIt;
      
      l++;
      i++;
      
    }


    matrix.endWrite();
  }

  protected:
  byte colorCount;  
  byte colorIndex = 0; 
  byte pos = 0;
  
  Palette* palette;
  String text;

  byte width = displayW/2;
  byte height = displayH;

  byte lineW = 4;
  byte lineP = 2;
  byte lineTotal = lineW + lineP;
  
};
/*
class MultiColorMessage : public Message {

  public:
  MultiColorMessage(String text) : Message(text) {}

  void showFrame() override {
    
    needRefresh = needRefresh || ticker->checkTime();
    
    if (needRefresh) {
      byte len = text.length();
      byte x = 1;
      byte y = 4;
      byte inc = 5;
      
      for (byte i = 0; i < len; i++) {
        char c = text[i];
        matrix.setCursor(x, y);
        matrix.setTextColor(colors[(colorIndex + i) % colorCount]);
        matrix.print(c);
        x += inc;
        
        needRefresh = false;
      }
      colorIndex = (colorIndex + 1) % colorCount;
    }
  }

  private:
  const byte colorCount = 12;
  color_t colors[12] = {COLOR(7,0,0), COLOR(7,4,0), COLOR(7,7,0), COLOR(4,7,0), COLOR(0,7,0), COLOR(0,7,4), COLOR(0,7,7), COLOR(0,4,7), COLOR(0,0,7), COLOR(4,0,7), COLOR(7,0,7), COLOR(7,0,4)};
  byte colorIndex = 0;
  Ticker* ticker = new Ticker(120);
  
};

class AnimateColorMessage : public Message {

  public:
  AnimateColorMessage(String text) : Message(text) {}

  void showFrame() override {
    
    needRefresh = needRefresh || ticker->checkTime();
    
    if (needRefresh) {
      
      Message::showFrame();
      colorIndex = (colorIndex + 1) % colorCount;
      color = colors[colorIndex];
    }
  }

  private:
  const byte colorCount = 12;
  color_t colors[12] = {COLOR(7,0,0), COLOR(7,4,0), COLOR(7,7,0), COLOR(4,7,0), COLOR(0,7,0), COLOR(0,7,4), COLOR(0,7,7), COLOR(0,4,7), COLOR(0,0,7), COLOR(4,0,7), COLOR(7,0,7), COLOR(7,0,4)};
  byte colorIndex = 0;
  Ticker* ticker = new Ticker(120);
  
};

Message* messages[] = {
  
  new AnimateColorMessage("YMNK"),
  new Message("chez"),
  new MultiColorMessage("OSCAAR"),
  new Message("MARLY", COLOR(0,7,7)),
  new Message("27/08"),
  new AnimateColorMessage("VIENS !!!"),
  new MultiColorMessage("(*^_^)")
};

byte messagesCount;
*/
#endif //MESSAGE_H
