
#define CVCLOCK A5
#define DISPLAY_SWITCH A4

#include <RGBmatrixPanel.h>
#include <MIDI.h>

#include "ColorsAndMatrix.h"
#include "Ticker.h"

#include "Palette.h"
#include "Squares.h"
#include "Sticks.h"
#include "Message.h"
#include "Rectangle.h"
#include "RectangleGroup.h"
#include "SquareTrail.h"
#include "RainDrops.h"
#include "Arrows.h"


color_t blueArray[] = {COLOR(0,0,7), COLOR(0,0,5), COLOR(0,0,3)};
Palette* blueTest = new Palette(3, blueArray);

color_t blueAndWhiteArray[] = {COLOR(0,0,7), COLOR(0,7,7), COLOR(7,7,7)};
Palette* blueAndWhite = new Palette(3, blueAndWhiteArray);

Palette* blue = new Palette(8, 0, 0, 7);
Palette* blueSmall = new Palette(4, 0, 0, 7);

Palette* redSmall = new Palette(4, 7, 0, 0);

Palette* rainbowP = new Palette(rainbowCount, rainbow);


Scene* scenes[] = {
  new Message("BRIGHTER", blueAndWhite),
  new RainDrops(blue),
  new Arrows(rainbowP),
  new SquareTrail(redSmall, true),
  new RectangleGroup(blueSmall),
  new Rectangle(blueSmall),
  new Sticks(blue),
  new Squares(),
  new Squares(false)
};

byte sceneIndex = 0;
byte sceneCount;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  Serial.begin(9600);
  sceneCount = sizeof(scenes)/sizeof(scenes[0]);

  matrix.begin();
  //messagesCount = sizeof(messages)/sizeof(messages[0]);
  
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleProgramChange(handleProgramChange);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  scenes[0]->prepareFrame();
}

/*
int check = 0;
int frequency = 4;
int height[2] = {0, 0};
int increment[2] = {0, 0};
*/
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

void handleProgramChange(byte channel, byte program) {
  sceneIndex = min(program, sceneCount - 1);
  scenes[sceneIndex]->prepareFrame();
}

bool cvInState = false;
bool isOtherDisplay = false;

Ticker ticker(2000);

void loop() {
  
  MIDI.read();
  
  bool newCvInState = analogRead(CVCLOCK) > 200;
  isOtherDisplay = analogRead(DISPLAY_SWITCH) > 200;

  bool tick = newCvInState && !cvInState;

  scenes[sceneIndex]->tick(tick);
  scenes[sceneIndex]->showFrame(isOtherDisplay);

  cvInState = newCvInState;

  
/*
  if (ticker.checkTime()) {
    index = (index + 1) % messagesCount;
    messages[index]->prepareFrame();
  }
*/
  

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
