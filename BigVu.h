
#ifndef BIG_VU_H
#define BIG_VU_H

//y=abs(((x+size)%(size*2))-size)

#include "Scene.h"

static int triangleMod(int value, int size) {
    return abs(((value+size)%(size*2))-size);
}

static int mirrorMod(int value, int size) {
    int remainder = value/size;
    if (remainder%2 == 0) {
        return value % size;
    } else {
        return size - 1 - (value % size); 
    }
}


class BigVu : public TickerScene {
public:
enum Mode {
  horizontal = 0,
  vertical
};
  
public:
  BigVu(Palette* palette, byte note, byte noteCount = 1, Mode mode = horizontal, bool mirrored = false) 
    : noteCount(noteCount), palette(palette), note(note), mode(mode), mirrored(mirrored) {

  }

  virtual ~BigVu() {
    delete palette;
  }
  
public:

    virtual void midiNote(byte noteValue) override {

        byte maxNote = mirrored ? noteCount/2 : noteCount;

        if (noteValue >= note && noteValue < (note + maxNote)) {
            byte vuIndex = noteValue - note;
            vuStates[vuIndex].reset();
            if (mirrored) {
                vuStates[noteCount - 1 - vuIndex].reset();
            }
        }
    } 

    virtual void draw() override {

        for (byte i = 0; i < noteCount; i++) {

            byte vuH, vuW, x, y;

            bool isHorizontal = (mode == horizontal);

            color_t color = palette->colors[mirrorMod(i, palette->size)];

            VuState* state = &vuStates[i];

            if (state->vuUp) {
                state->vuSize += getRiseAmount();
            }

            switch(mode) {

                case horizontal : {

                    x = isOtherDisplay ? (displayHalfW - state->vuSize) : (state->vuUp ? 0 : state->vuSize);
                    y = i*vuH;

                    vuW = state->vuUp ? state->vuSize : 2;
                    vuH = displayH/noteCount;
                }   break;

                case vertical : {

                    vuW = displayW/noteCount;

                    x = (i * vuW);
                    y = displayH - vuStates[i].vuSize;

                    vuH = state->vuUp ? vuStates[i].vuSize : 1;
                }   break;
            }

            if (state->vuUp) {
            
                matrix.fillRect(x, y, vuW, vuH, color);
            
                if (state->vuSize >= (isHorizontal ? displayHalfW : displayH)) {
                    state->vuUp = false;
                }

            } else if (state->vuUp == false && state->vuSize >= 0) {
            
                matrix.fillRect(x, y, vuW, vuH, clearColor());
                state->vuSize = state->vuSize - (isHorizontal ? 2 : 0.75f);
            }
        }
    }

    virtual float getRiseAmount() {
        return mode == horizontal ? 16 : 8;
    }

protected:
    VuState vuStates[16];
    byte noteCount;

private: 
    Palette* palette;
    byte note;
    Mode mode;
    bool mirrored;
  
};


#endif //BIG_VU_H
