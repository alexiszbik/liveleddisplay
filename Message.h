
#ifndef MESSAGE_H
#define MESSAGE_H

class Message : public Scene {
  
  public:
  Message(String text, color_t color = COLOR(7,0,0)) {
    this->text = text;
    this->color = color;
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
    matrix.setTextSize(1);
    matrix.setTextColor(color);
    matrix.setTextWrap(false);
    drawCentreString(text);
  }

  protected:
  color_t color = COLOR(7,0,0);
  String text;
  
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
