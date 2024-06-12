
#ifndef Intro_h
#define Intro_h

#include "Scene.h"
#include "Ticker.h"

class Intro : public SquareScene {
    
public:
    Intro() : SquareScene(8) {
    }
    
    virtual ~Intro() {
    }
    
    virtual void showFrame(bool _isOtherDisplay) override {
        Scene::showFrame(_isOtherDisplay);
        
        if (ticker.checkTime()) {
            needRefresh = true;
            offset++;
            offset = offset % 12;
        }
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
        } if (noteValue == 54) {
            state = stateD;
        } if (noteValue >= 68 && noteValue <= 83 && (state >= stateC)) {
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
                clearScreen();
                if (isOtherDisplay) {
                    index -= 8;
                }
                byte r = 2 + (getRandom()%6);
                drawSquare(index, COLOR(r,r,r));
                
            } break;
            case stateC :
            case stateD : {
                
                byte parts = 16;
                byte width = displayW/parts;
                for (int x = 0; x < index + 1; x++) {
                    byte posx = x - (isOtherDisplay ? (parts/2) : 0);
                    byte hw = width/2;
                    if (posx>=0) {
                        if (state == stateC) {
                            matrix.fillRect(posx * width, 0, hw, displayH, COLOR(2,2,2));
                            matrix.fillRect(posx * width + hw, 0, hw, displayH, COLOR(7,7,7));
                        } else {
                            for (int y = 0; y < displayH; y++) {
                                byte cColor = y + x + offset;
                                byte cIndex = cColor % rainbow.size;
                                matrix.fillRect(posx * width, y, hw, 1, rainbow.colors[cIndex]);
                                cIndex = (cColor + 6) % rainbow.size;
                                matrix.fillRect(posx * width + hw, y, hw, 1, rainbow.colors[cIndex]);
                            }
                        }
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
        stateD
    };
    
    int index = 0;
    byte offset = 0;
    IntroState state = clear;
    IntroState previousState = clear;
    
    int iMap[16] = {5,9,11,3,8,4,12,0,14,1,6,15,13,2,7,10};
    
    Ticker ticker = Ticker(20);
    Palette rainbow = RainbowPalette();
};


#endif /* Intro_h */
