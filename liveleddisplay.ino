
#define CVCLOCK A5
#define DISPLAY_SWITCH A4

#include <RGBmatrixPanel.h>
#include <MIDI.h>

#include "ColorsAndMatrix.h"

#include "Palette.h"
#include "Sticks.h"
#include "Rectangle.h"
#include "RectangleGroup.h"
#include "Explode.h"
#include "RainDrops.h"
#include "Arrows.h"
#include "FlashingSign.h"
#include "SquareDrops.h"
#include "RandomYMNK.h"
#include "BigYMNK.h"
#include "BigVu.h"
#include "AutoVu.h"
#include "Kaomojis.h"
#include "Osc.h"
#include "PixNoise.h"
#include "Turnstile.h"
#include "Vortex.h"
#include "StarTour.h"
#include "Circles.h"
#include "Hearth.h"
#include "Intro.h"

static inline Palette* bluePalette(byte size = 8) {
  return new Palette(size, 0, 0, 7);
}

static inline Palette* redPalette(byte size = 8) {
  return new Palette(size, 7, 0, 0);
}

#define PINK_P new Palette(8, 7, 0, 7)

//note : PROGMEM don't do shit here
Scene* scene = NULL;
byte currentProgram = 0;

bool isPlaying = false;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  Serial.begin(9600);

  matrix.begin();
  matrix.setTextWrap(false);
  
  delay(1000); 

  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleProgramChange(handleProgramChange);
  MIDI.begin(16);

  MIDI.setHandleStart(handleStart);
  MIDI.setHandleStop(handleStop);

  scene = new SquareDrops(new RainbowPalette(), SquareDrops::randomOnce);

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
      /*case 0 : scene = new Squares(new RainbowPalette());
        break;*/

      //Brighter Beat
      case 2 : scene = new BigVu(new VuPalette(), 60, 4, BigVu::verticalWide);
        break;

      //Brighter Drop
      /*case 4 : scene = new Squares(new RainbowPalette());
        break;*/

      //Say : Brighter
      case 5 : scene = new FlashingSign(new Palette(COLOR(0,0,7), COLOR(0,7,7), COLOR(7,7,7)), FlashingSign::brighter, 3);
        break;



      //End Brighter // Expect the Unexpected
      case 6 : scene = new SquareDrops(bluePalette(), SquareDrops::randDrops);
        break;

        
     
      //Expect the Unexpected, + drums
      /*case 10 : scene = new RandomYMNK(new RainbowPalette());
        break;*/


      //Pers intro
      case 15 : scene = new Sticks(redPalette());
        break;

      //Pers Kick
      case 16 : scene = new BigVu(new Palette(COLOR(7,0,0)), 36);
        break;

      //Pers Drop
      case 17 : scene = new RectangleGroup(bluePalette(4));
        break;

      //Pers End
      
      case 18 : scene = new Kaomojis(new RainbowPalette());
        break;

      case 19 : scene = new PixNoise();
        break;
      case 20 : scene = new SquareDrops(PINK_P, SquareDrops::wash);
        break;


      //Hopes
      //intro
      case 22 : scene = new RainDrops(bluePalette());
        break;
      //toms
      case 23 : scene = new BigVu(new Palette(COLOR(0,0,7)), 48, 4, BigVu::Mode::verticalMirrored);
        break;

        

        //Water
      
      case 24 : scene = new Osc(new Palette(COLOR(0,7,7)));
         break;

      case 25 : scene = new Turnstile();
         break;

      case 26 : scene = new Osc(new Palette(COLOR(0,0,7), COLOR(0,7,7), COLOR(7,7,7)));
         break;

         

      //Animaux intro
      case 27 : scene = new SquareDrops(redPalette(4),  SquareDrops::trail);
        break;
      //Animaux kick
      case 28 : scene = new Arrows();
        break;
      //Animaux end
      case 29 : scene = new BigYMNK(new RainbowPalette());
        break;

     

      // BiBimBap
      case 35 : scene = new BigVu(new Palette(COLOR(0,7,0)), 36, 2);
        break;
      case 36 : scene = new Vortex();
        break;
        /*
      //Raindrops Rainbow
      case 40 : scene = new RainDrops(new RainbowPalette());
        break;
*/

      //Tir3d of Technology
      case 42 : scene = new StarTour();
        break;

       //Friendship & Bravery
      case 43 : scene = new AutoVu(new Palette(8,0,0,7, true));
        break;

      case 44 : scene = new Circles(bluePalette());
        break;

      case 45 : scene = new AutoVu(new RainbowPalette());
        break;
     
      case 46 : scene = new FlashingSign(new Palette(COLOR(7,7,7)), FlashingSign::friendship, 1);
        break;

      case 47 : scene = new FlashingSign(new RainbowPalette(), FlashingSign::friendship, 1);
        break;
      
    
      //test hearth
      case 50 : scene = new Circles(redPalette(), true);
        break;


      case 52 : scene = new Intro();
        break;
      
         //Fill outside
      case 53 : scene = new BigYMNK(new RainbowPalette(), true);
        break;

      case 54 : scene = new FlashingSign(new Palette(COLOR(7,7,7)), FlashingSign::version, 0);
        break;

      case 59 : scene = new Explode();
        break;

      case 64 : scene = new FlashingSign(new RainbowPalette(), FlashingSign::front, 1);
        break;


  
      default: scene = new SquareDrops(new RainbowPalette(), SquareDrops::randomOnce);
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
