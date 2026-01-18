
#define CVCLOCK A5
#define DISPLAY_SWITCH A4

#include <MIDI.h>

#include "ColorsAndMatrix.h"

#include "Palette.h"
#include "Sticks.h"
#include "Rectangle.h"
#include "RectangleGroup.h"
#include "RainDrops.h"
#include "Arrows.h"
#include "FlashingSign.h"
#include "MovingSign.h"
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
#include "Gfx.h"
#include "Intro.h"
#include "Explode.h"
#include "Plasma.h"
#include "Lasers.h"
#include "Spiral.h"


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
byte midiTick = 0;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  Serial.begin(9600);

  matrix.begin();

  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleProgramChange(handleProgramChange);
  MIDI.setHandleStart(handleStart);
  MIDI.setHandleStop(handleStop);
  MIDI.setHandleClock(handleClock);
  MIDI.turnThruOff();
  MIDI.begin(16);

  delay(500);

  matrix.println("YMNK live LED matrix");  // Default text color is white

  matrix.show();

  matrix.setTextWrap(false);

  delay(2000);

  // AFTER DRAWING, A show() CALL IS REQUIRED TO UPDATE THE MATRIX!

  clearScreen();
  matrix.show();
  //scene = new Circles(redPalette(), true);
  scene = new SquareDrops(new RainbowPalette(), SquareDrops::randomOnce);
  //scene = new Osc(new Palette(COLOR(0,0,7), COLOR(0,7,7), COLOR(7,7,7)));
  //scene = new Osc(new Palette(COLOR(0,7,7)));
}

void handleStart() {
  isPlaying = true;
  midiTick = 0;
}

void handleStop() {
  clearScreen();
  isPlaying = false;
  matrix.show();
}


void handleNoteOn(byte channel, byte note, byte velocity) {
  if (velocity > 0) {
    scene->midiNote(note);
  }
}


void handleClock() {
  if (midiTick % 6 == 0) {
    scene->midiSync();
  }
  midiTick = midiTick + 1;
  midiTick = midiTick % 96;
}

void handleProgramChange(byte channel, byte program) {
  if (program != currentProgram) {

    delete scene;
    scene = NULL;

    switch (program) {

      //Brighter Beat
      case 2:
        scene = new BigVu(new VuPalette(), 60, 4, BigVu::vertical);
        break;

      case 4:
        scene = new Spiral();
        break;

      //Say : Brighter
      case 5:
        scene = new FlashingSign(new Palette(COLOR(0, 0, 7), COLOR(0, 7, 7), COLOR(7, 7, 7)), FlashingSign::brighter, 3);
        break;



      //End Brighter // Expect the Unexpected
      case 6:
        scene = new SquareDrops(bluePalette(), SquareDrops::randDrops);
        break;

      //Plasma
      case 7:
        scene = new Plasma();
        break;

      //Lasers
      case 8:
        scene = new Lasers();
        break;
        //Lasers
      case 9:
        scene = new Gfx(new Palette(COLOR(7, 4, 0)), GfxEnum::gfx_smiley, Gfx::EGfxMode::gfxMode_normal, Gfx::EYmove::noMove, false, true);
        break;




      //Expect the Unexpected, + drums
      case 10:
        scene = new RandomYMNK(new RainbowPalette());
        break;


      //Pers intro
      case 15:
        scene = new Sticks(redPalette());  //Weird but okay!
        break;

      //Pers Kick
      case 16:
        scene = new BigVu(new Palette(COLOR(7, 0, 0)), 36, 1, BigVu::Mode::horizontal, true);
        break;

      //Pers Drop
      case 17:
        scene = new RectangleGroup(bluePalette(4));
        break;

        //Pers End

      case 18:
        scene = new Kaomojis(new RainbowPalette());
        break;

      case 19:
        scene = new PixNoise();
        break;
      case 20:
        scene = new SquareDrops(new Palette(7, 7, 0, 7), SquareDrops::wash);
        break;


      //Hopes
      //intro
      case 22:
        scene = new RainDrops(bluePalette());
        break;
      //toms
      case 23:
        scene = new BigVu(new Palette(COLOR(0, 0, 7)), 48, 4, BigVu::Mode::vertical, true);
        break;


        //Water

      case 24:
        scene = new Osc(new Palette(COLOR(0, 7, 7)));
        break;

      case 25:
        scene = new Turnstile();
        break;

      case 26:
        scene = new Osc(new Palette(COLOR(0, 0, 7), COLOR(0, 7, 7), COLOR(7, 7, 7)));
        break;



      //Animaux intro
      case 27:
        scene = new SquareDrops(redPalette(), SquareDrops::trail);
        break;
      //Animaux kick
      case 28:
        scene = new Arrows();
        break;
      //Animaux end
      case 29:
        scene = new BigYMNK(new RainbowPalette());
        break;

      //FANTASY
      case 30:
        scene = new MovingSign(new Palette(COLOR(0, 0, 7)), MovingSign::fantasy);
        break;

      case 31:
        scene = new MovingSign(new RainbowPalette(), MovingSign::fantasy);
        break;

      case 32:
        scene = new MovingSign(new RainbowPalette(), MovingSign::fantasy, true, true);
        break;



      // BiBimBap
      case 35:
        scene = new BigVu(new Palette(COLOR(0, 7, 0)), 36, 2, BigVu::Mode::horizontal, true);
        break;
      case 36:
        scene = new Vortex();
        break;

      //Raindrops Rainbow
      case 40:
        scene = new RainDrops(new RainbowPalette());
        break;


      //Tir3d of Technology
      case 42:
        scene = new StarTour();
        break;

        //Friendship & Bravery
      case 43:
        scene = new AutoVu(new Palette(COLOR(0, 0, 7)));
        break;

      case 44:
        scene = new Circles(bluePalette());
        break;

      case 45:
        scene = new AutoVu(new VuPalette2());
        break;

      case 46:
        scene = new FlashingSign(new Palette(COLOR(7, 7, 7)), FlashingSign::friendship, 1);
        break;

      case 47:
        scene = new FlashingSign(new RainbowPalette(), FlashingSign::friendship, 1);
        break;


      //test hearth
      case 50:
        scene = new Gfx(new Palette(COLOR(7, 0, 0)), GfxEnum::gfx_hearth);
        break;

      case 51:
      //Gfx(Palette* palette, GfxEnum gfxEnum, EGfxMode mode = gfxMode_normal, EYmove yMove = noMove, bool colorMove = false, bool isMidiSynced = false)
        scene = new Gfx(new RainbowPalette(), GfxEnum::gfx_hearth, Gfx::EGfxMode::gfxMode_plainWithContour,  Gfx::EYmove::noMove, true);
        break;


      case 52:
        scene = new Intro();
        break;

        //Fill outside
      case 53:
        scene = new BigYMNK(new RainbowPalette(), true);
        break;

      case 54:
        scene = new FlashingSign(new Palette(COLOR(7, 7, 7)), FlashingSign::version, 0);
        break;

      case 59:
        scene = new Explode();
        break;

      case 64:
        scene = new BigVu(new VuPalette(), 36, 4, BigVu::vertical);
        break;

      case 65:
        scene = new Sticks(new RainbowPalette(), 2, 3, 1);
        break;

        //L'amour
      case 67:
        scene = new SquareDrops(new RainbowPalette(), SquareDrops::wash);
        break;
      case 68:
        scene = new Gfx(new RainbowPalette(), GfxEnum::gfx_star, Gfx::EGfxMode::gfxMode_normal,  Gfx::EYmove::bipolar, true, true);
        break;


      case 70:
        scene = new Gfx(new Palette(COLOR(7, 0, 0)), GfxEnum::gfx_tear, Gfx::EGfxMode::gfxMode_plain,  Gfx::EYmove::diagonalFall);
        break;
      case 71:
        scene = new Gfx(new Palette(COLOR(7, 0, 0)), GfxEnum::gfx_tear, Gfx::EGfxMode::gfxMode_plain,  Gfx::EYmove::falling);
        break;


      case 80:
        scene = new MovingSign(new Palette(COLOR(0, 0, 7)), MovingSign::delaurentis, false, false, false);
        break;
      case 81:
        scene = new BigYMNK(new RainbowPalette());
        break;
      case 82:
        scene = new MovingSign(new Palette(7, 0, 7, 7), MovingSign::douran, false, false, false);
        break;
      case 83:
        scene = new FlashingSign(new Palette(COLOR(0, 0, 7), COLOR(0, 7, 7), COLOR(7, 7, 7)), FlashingSign::deadChic, 3);
        break;
      case 84:
        scene = new FlashingSign(new Palette(COLOR(7, 0, 0)), FlashingSign::vss, 1, true);
        break;
      case 85:
        scene = new MovingSign(new Palette(COLOR(0, 7, 0)), MovingSign::bv3, false, false, false);
        break;
      case 86:
        scene = new FlashingSign(new Palette(COLOR(0, 0, 4), COLOR(0, 0, 7), COLOR(0, 4, 7)), FlashingSign::elvett, 3);
        break;
      case 87:
        scene = new MovingSign(new Palette(COLOR(0, 0, 7)), MovingSign::nouvelleVague, false, false, false);
        break;
      case 88:
        scene = new MovingSign(new Palette(COLOR(7, 0, 0)), MovingSign::prettyInside, false, false, false);
        break;
      case 89:
        scene = new FlashingSign(new RainbowPalette(), FlashingSign::sonia, 2, true);
        break;
      case 90:
        scene = new FlashingSign(new Palette(COLOR(0, 7, 0)), FlashingSign::ilEstVilaine, 1, true);
        break;





      default:
        scene = new SquareDrops(new RainbowPalette(), SquareDrops::randomOnce);
        break;
    }
    scene->prepareFrame();

    currentProgram = program;
  }
}

bool cvInState = false;
bool debug = true;
long debugTimer = 0;

void loop() {

  for (byte i = 0; i < 8; i++) {
    MIDI.read();
  }

  bool newCvInState = digitalRead(CVCLOCK);

  bool tick = newCvInState && !cvInState;

  if (debug) {
    long newTimer = millis();
    if ((newTimer - debugTimer) > 120) {
      tick = true;
      debugTimer = newTimer;
    }
  }

  scene->tick(tick);

  if (isPlaying || debug) {
    scene->showFrame();
    matrix.show();
  }

  cvInState = newCvInState;
}
