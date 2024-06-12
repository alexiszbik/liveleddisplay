
#ifndef Intro_h
#define Intro_h

#include "Scene.h"

class Intro : public SquareScene {
    
public:
    Intro() : SquareScene(8) {
    }
    
    virtual ~Intro() {
    }
    
    virtual void midiNote(byte noteValue) override {
        if (noteValue == 36) {
            state = stateA;
        } if (noteValue >= 37 && noteValue <= 51) {
            byte s = (noteValue - 37);
            index = iMap[s];
            state = stateB;
        } if (noteValue == 52) {
            state = stateC;
        } if (noteValue >= 68 && noteValue <= 83 && (state == stateC)) {
          index = (noteValue - 68);
        } if (noteValue == 84) {
          state = clear;
        }
        
        needRefresh = true;
    }
    
    virtual void draw() override {

      
        if (previousState != state) {
          previousState = state;
          clearScreen();
        }
        
        switch(state) {
            case clear : {
                clearScreen();
            } break;
            case stateA : {
              matrix.writeFastHLine(0, displayHalfH, displayHalfW, COLOR(7,7,7));

            } break;
            case stateB : {
                
                if (isOtherDisplay) {
                    index -= 8;
                }
                byte r = 2 + (getRandom()%6);
                drawSquare(index, COLOR(r,r,r));
                
            } break;
            case stateC : {
                
                byte parts = 16;
                byte width = displayW/parts;
                for (int x = 0; x < index; x++) {
                    x = x - (isOtherDisplay ? (parts/2) : 0);
                    byte hw = width/2;
                    if (x>=0) {
                      matrix.fillRect(x * width, 0, hw, displayH, COLOR(2,2,2));
                      matrix.fillRect(x * width + hw, 0, hw, displayH, COLOR(7,7,7));
                    } 
                }
                
            } break;
        }
        
    }
    
private:
    enum IntroState {
        clear,
        stateA,
        stateB,
        stateC,
    };
    
    int index = 0;
    IntroState state = clear;
    IntroState previousState = clear;

    int iMap[16] = {5,9,11,3,8,4,12,0,14,1,6,15,13,2,7,10};
};


#endif /* Intro_h */
