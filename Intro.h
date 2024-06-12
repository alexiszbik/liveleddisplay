
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
            sqrPos = (noteValue - 37);
            state = stateB;
        } if (noteValue == 52) {
            state = stateC;
        }
        
        needRefresh = true;
    }
    
    virtual void draw() override {
        
        switch(state) {
            case clear : {
                
            } break;
            case stateA : {
                
            } break;
            case stateB : {
                
                if (isOtherDisplay) {
                    sqrPos -= 8;
                }
                drawSquare(sqrPos, COLOR(0,7,7));
                
            } break;
            case stateC : {
                
                byte parts = 16;
                byte width = displayW/parts;
                for (byte x = 0; x < parts; x++) {
                    byte hw = width/2;
                    matrix.fillRect(x * width, 0, hw, displayH, COLOR(2,2,2));
                    matrix.fillRect(x * width + hw, 0, hw, displayH, COLOR(7,7,7));
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
    
    int sqrPos;
    IntroState state;
};


#endif /* Intro_h */
