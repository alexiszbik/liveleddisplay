
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
#include "BigVu.h"
#include "Kaomojis.h"


color_t blueArray[] = {COLOR(0,0,7), COLOR(0,0,5), COLOR(0,0,3)};
Palette* blueTest = new Palette(3, blueArray);

color_t vuPaletteArray[] = {COLOR(0,0,7), COLOR(0,7,0), COLOR(7,7,0), COLOR(7,0,0)};
Palette* vuPalette = new Palette(4, vuPaletteArray);

color_t blueAndWhiteArray[] = {COLOR(0,0,7), COLOR(0,7,7), COLOR(7,7,7)};
Palette* blueAndWhite = new Palette(3, blueAndWhiteArray);

Palette* blue = new Palette(8, 0, 0, 7);
Palette* blueSmall = new Palette(4, 0, 0, 7);

Palette* red = new Palette(8, 7, 0, 0);
Palette* redSmall = new Palette(4, 7, 0, 0);

Palette* rainbowP = new Palette(rainbowCount, rainbow);

/*
Scene* scenes[] = {
  new BigVu(vuPalette),
  //new QuadVu(vuPalette),
  ///new VuMeter(vuPalette),
  //new BigYMNK(rainbowP),
  //new RandomYMNK(rainbowP),
  //new SquareDrops(blue),
  new FlashingSign("BRIGHTER", blueAndWhite),
  new RainDrops(blue),
  new Arrows(rainbowP),
  new SquareTrail(redSmall, true),
  new RectangleGroup(blueSmall),
  new Rectangle(blueSmall),
  new Sticks(blue),
  new Squares(),
  new Squares(false)
};*/

Scene* scene = NULL;
byte currentProgram = 0;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  Serial.begin(9600);

  matrix.begin();
  
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleProgramChange(handleProgramChange);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  scene = new Squares();

  scene->prepareFrame();
}


void handleNoteOn(byte channel, byte note, byte velocity) {
  if (velocity > 0) {
    scene->midiNote(note);
  }
}

void handleProgramChange(byte channel, byte program) {
  if (program != currentProgram) {
  
    delete scene;
    scene = NULL;
    
    switch(program) {
      
      //Intro
      case 0 : scene = new Squares();
        break;

      //Brighter Beat
      case 2 : scene = new VuMeter(vuPalette);
        break;

      //Brighter Drop
      case 4 : scene = new Squares();
        break;

      //Say : Brighter
      case 5 : scene = new FlashingSign(blueAndWhite);
        break;



      //End Brighter // The Great Escape
      case 6 : scene = new SquareDrops(blue);
        break;

        
     
      //The Great Scape, + drums
      case 10 : scene = new RandomYMNK(rainbowP);
        break;


      //THANK you ???

      //Pers intro
      case 15 : scene = new Sticks(red);
        break;

      //Pers Kick
      case 16 : scene = new BigVu(red);
        break;

      //Pers Drop
      case 17 : scene = new RectangleGroup(blueSmall);
        break;

      //Pers End
      /*case 18 : scene = new Kaomojis(rainbowP);
        break;*/


      //Hopes
      //intro
      case 22 : scene = new RainDrops(blue);
        break;
      //toms
      case 23 : scene = new QuadVu(blue);
        break;

      //Animaux intro
      case 27 : scene = new SquareTrail(redSmall, true);
        break;
      //Animaux kick
      case 28 : scene = new Arrows(rainbowP);
        break;
      //Animaux end
      case 29 : scene = new BigYMNK(rainbowP);
        break;
    
  
      default: scene = new Squares();
        break;
    }
    scene->prepareFrame();

    currentProgram = program;
  }
}

bool cvInState = false;
bool isOtherDisplay = false;

void loop() {
  
  MIDI.read();
  
  bool newCvInState = analogRead(CVCLOCK) > 200;
  isOtherDisplay = analogRead(DISPLAY_SWITCH) > 200;

  bool tick = newCvInState && !cvInState;

  scene->tick(tick);
  scene->showFrame(isOtherDisplay);

  cvInState = newCvInState;

}
