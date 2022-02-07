
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
#include "Osc.h"

#define BLUE_P new Palette(8, 0, 0, 7)
#define BLUE_P_S new Palette(4, 0, 0, 7)

#define RED_P new Palette(8, 7, 0, 0)
#define RED_P_S new Palette(4, 7, 0, 0)


Scene* scene = NULL;
byte currentProgram = 0;

bool isPlaying = false;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  Serial.begin(9600);

  matrix.begin();
  
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleProgramChange(handleProgramChange);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  MIDI.setHandleStart(handleStart);
  MIDI.setHandleStop(handleStop);

  scene = new Squares(new RainbowPalette());

  scene->prepareFrame();
}

void handleStart() {
  isPlaying = true;
}

void handleStop() {
  clearScreen();
  isPlaying = false;
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
      case 0 : scene = new Squares(new RainbowPalette());
        break;

      //Brighter Beat
      case 2 : scene = new VuMeter(new VuPalette());
        break;

      //Brighter Drop
      case 4 : scene = new Squares(new RainbowPalette());
        break;

      //Say : Brighter
      case 5 : scene = new FlashingSign(new Palette(COLOR(0,0,7), COLOR(0,7,7), COLOR(7,7,7)));
        break;



      //End Brighter // The Great Escape
      case 6 : scene = new SquareDrops(BLUE_P);
        break;

        
     
      //The Great Scape, + drums
      case 10 : scene = new RandomYMNK(new RainbowPalette());
        break;

       

      //THANK you ???

      //Pers intro
      case 15 : scene = new Sticks(RED_P);
        break;

      //Pers Kick
      case 16 : scene = new BigVu(RED_P, 36);
        break;

      //Pers Drop
      case 17 : scene = new RectangleGroup(BLUE_P_S);
        break;

      //Pers End
      case 18 : scene = new Kaomojis(new RainbowPalette());
        break;

      //Water
      case 20 : scene = new Osc();
         break;



      //Hopes
      //intro
      case 22 : scene = new RainDrops(BLUE_P);
        break;
      //toms
      case 23 : scene = new QuadVu(BLUE_P);
        break;

      //Animaux intro
      case 27 : scene = new SquareTrail(RED_P_S, true);
        break;
      //Animaux kick
      case 28 : scene = new Arrows();
        break;
      //Animaux end
      case 29 : scene = new BigYMNK(new RainbowPalette());
        break;
    
  
      default: scene = new Squares(new RainbowPalette());
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
  
  if (isPlaying) {
    scene->showFrame(isOtherDisplay);
  }

  cvInState = newCvInState;

}
