#define CLK  8  
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

#define CVCLOCK A5
#define DISPLAY_SWITCH A4

#include <RGBmatrixPanel.h>
#include <MIDI.h>

#include "Ticker.h"

// --- COLOR & MATRIX & etc ...

#define displayW 32 * 2
#define displayH 16

typedef uint16_t color_t;

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

#define COLOR(r,g,b) matrix.Color333(r,g,b)

void clearScreen() {
  matrix.fillScreen(COLOR(0, 0, 0));
}

const byte rainbowCount = 12;
color_t rainbow[rainbowCount] = {COLOR(7,0,0), COLOR(7,4,0), COLOR(7,7,0), COLOR(4,7,0), COLOR(0,7,0), COLOR(0,7,4), COLOR(0,7,7), COLOR(0,4,7), COLOR(0,0,7), COLOR(4,0,7), COLOR(7,0,7), COLOR(7,0,4)};

color_t randomColor() {
  byte chosen = random(rainbowCount);
  return rainbow[chosen];  

}

// ***********


#include "Squares.h"

Squares scene;

MIDI_CREATE_DEFAULT_INSTANCE();

class Message {
  
  public:
  Message(String text, color_t color = COLOR(7,0,0)) {
    this->text = text;
    this->color = color;
  }

  void drawCentreString(const String &buf) {
    matrix.setCursor(0, 0);
    int16_t x1, y1;
    uint16_t w, h;
    matrix.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);
    matrix.setCursor(displayW/2 - w/2, displayH/2 - h/2);
    matrix.print(buf);
  }


  virtual void prepareFrame() {
    initFrame();
    needRefresh = true;
  }

  virtual void showFrame() {
    if (needRefresh) {
      
      matrix.setTextSize(1);
      matrix.setTextColor(color);
      drawCentreString(text);
      needRefresh = false;
    }
  }

  protected:
  void initFrame() {
    clearScreen();
    matrix.setCursor(0, 0);
  }

  protected:
  color_t color = COLOR(7,0,0);
  String text;
  bool needRefresh = true;
  
};

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

void setup() {
  Serial.begin(9600);

  matrix.begin();
  messagesCount = sizeof(messages)/sizeof(messages[0]);
  
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  scene.prepareFrame();
}

int check = 0;

int frequency = 4;
int height[2] = {0, 0};
int increment[2] = {0, 0};
bool boom[2] = {false, false};

void handleNoteOn(byte channel, byte note, byte velocity) {
  if (velocity > 0) {
    if (note == 48) {
      boom[0] = true;
    } else {
      boom[1] = true;
    }
  }
}

byte index = 0;
bool cvInState = false;
bool isOtherDisplay = false;

Ticker ticker(2000);

void loop() {
  MIDI.read();

  bool newCvInState = analogRead(CVCLOCK) > 200;
  isOtherDisplay = analogRead(DISPLAY_SWITCH) > 200;

  bool tick = newCvInState && !cvInState;

  scene.tick(tick);
  scene.showFrame(isOtherDisplay);
  
/*
  if (ticker.checkTime()) {
    index = (index + 1) % messagesCount;
    messages[index]->prepareFrame();
  }
*/
  

  //messages[index]->showFrame();

  cvInState = newCvInState;

  /*
  check = (check + 1) % 400;

  if (check != 0) return;

  for (byte i = 0; i < 2; i++) {
    if (boom[i]) {
      increment[i] = 8;
    }
  
    height[i] = fmax(height[i] + increment[i], 0);
    
    if (height[i] >= 0) {
      if (increment[i] > 0) {
        matrix.fillRect(i*16, 16 - height[i], 16, 8, matrix.Color333(0, 4, i == 1 ? 4 : 0));
      } else {
        matrix.fillRect(i*16, 15 - height[i], 16, 1, matrix.Color333(0, 0, 0));
      }
    }
    
    if (height[i] >= 16 ) {
      increment[i] = -1;
      boom[i] = false;
    }
  }
  */
}
