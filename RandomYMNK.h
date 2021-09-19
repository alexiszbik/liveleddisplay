
#ifndef RANDOM_YMNK_H
#define RANDOM_YMNK_H

#include "Scene.h"

#define TILE_SIZE 8
#define TILE_X_MAX 8
#define TILE_Y_MAX 2

#define LETTER_COUNT 4

class RandomYMNK : public Scene {
  
public:
  struct Point {
    byte x = 0;
    byte y = 0;
  };

  RandomYMNK(Palette* palette) : palette(palette)  {

  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;
    }
  }

  bool verify(byte x, byte y, byte letterIndex) {
    if (letterIndex == 0) {
      return true;
    }

    for (byte i = 0; i < letterIndex; i++) {
      if ((x == positions[i].x) && (y == positions[i].y)) {
        return false;
      }
    }


    return true;
  }

  virtual void draw() override {

    matrix.setTextSize(1);
    matrix.setTextWrap(false);

    clearScreen();

    byte xOffset = isOtherDisplay ? displayW/2 : 0;
    
    for (byte i = 0; i < LETTER_COUNT; i++) {
      char letter = letters[i];
      byte colorIndex = random(1000) % palette->size;
      matrix.setTextColor(palette->colors[colorIndex]);

      byte x, y; 

      do {
        x = (random(1000) % TILE_X_MAX) * TILE_SIZE;
        y = (random(1000) % TILE_Y_MAX) * TILE_SIZE;
        
        positions[i].x = x;
        positions[i].y = y;

      } while ( verify(x, y, i) == false); 
      
      matrix.setCursor(x - xOffset, y);
      matrix.print(letter);
    }
  }


private:
  Palette* palette;
  const char letters[LETTER_COUNT] = {'Y', 'M', 'N', 'K'};

  Point positions[LETTER_COUNT];

};

#endif //RANDOM_YMNK_H
