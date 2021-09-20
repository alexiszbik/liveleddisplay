
#define CVCLOCK A5
#define DISPLAY_SWITCH A4

#include <RGBmatrixPanel.h>
#include <MIDI.h>

#include "ColorsAndMatrix.h"
#include "Ticker.h"

#include "Palette.h"
#include "Squares.h"
#include "Sticks.h"
#include "Rectangle.h"
#include "RectangleGroup.h"
#include "SquareTrail.h"
#include "RainDrops.h"
#include "Arrows.h"
#include "FlashingSign.h"
#include "SquareDrops.h"
#include "RandomYMNK.h"
#include "BigYMNK.h"
#include "VuMeter.h"
#include "QuadVu.h"


color_t blueArray[] = {COLOR(0,0,7), COLOR(0,0,5), COLOR(0,0,3)};
Palette* blueTest = new Palette(3, blueArray);

color_t vuPaletteArray[] = {COLOR(0,0,7), COLOR(0,7,0), COLOR(7,7,0), COLOR(7,0,0)};
Palette* vuPalette = new Palette(4, vuPaletteArray);

color_t blueAndWhiteArray[] = {COLOR(0,0,7), COLOR(0,7,7), COLOR(7,7,7)};
Palette* blueAndWhite = new Palette(3, blueAndWhiteArray);

Palette* blue = new Palette(8, 0, 0, 7);
Palette* blueSmall = new Palette(4, 0, 0, 7);

Palette* redSmall = new Palette(4, 7, 0, 0);

Palette* rainbowP = new Palette(rainbowCount, rainbow);


Scene* scenes[] = {
  new QuadVu(vuPalette),
  ///new VuMeter(vuPalette),
  //new BigYMNK(rainbowP),
  //new RandomYMNK(rainbowP),
  //new SquareDrops(blue),
  /*new FlashingSign("BRIGHTER", blueAndWhite),
  new RainDrops(blue),
  new Arrows(rainbowP),
  new SquareTrail(redSmall, true),
  new RectangleGroup(blueSmall),
  new Rectangle(blueSmall),
  new Sticks(blue),
  new Squares(),
  new Squares(false)*/
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


void handleNoteOn(byte channel, byte note, byte velocity) {
  if (velocity > 0) {
    scenes[0]->midiNote(note);
  }
}

void handleProgramChange(byte channel, byte program) {
  sceneIndex = min(program, sceneCount - 1);
  scenes[sceneIndex]->prepareFrame();
}

bool cvInState = false;
bool isOtherDisplay = false;

void loop() {
  
  MIDI.read();
  
  bool newCvInState = analogRead(CVCLOCK) > 200;
  isOtherDisplay = analogRead(DISPLAY_SWITCH) > 200;

  bool tick = newCvInState && !cvInState;

  scenes[sceneIndex]->tick(tick);
  scenes[sceneIndex]->showFrame(isOtherDisplay);

  cvInState = newCvInState;

 
}
