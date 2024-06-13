
#ifndef Intro_h
#define Intro_h

#include "Scene.h"
#include "Ticker.h"

class Intro : public Scene {
    
public:
    Intro() {
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
            clearScreen();
            index = 0;
        } if (noteValue >= 68 && noteValue <= 83 && (state == stateC)) {
            index = (noteValue - 68);
        } if (noteValue == 84) {
            state = clear;
        }
        
        needRefresh = true;
    }
    
    void drawSquare(int index, color_t color, bool fullWidth = false) {
        byte sqrSize = 8;
        byte perW = ((fullWidth ? displayW : displayHalfW)/sqrSize);
        byte xPos = index % perW;
        byte yPos = index / perW;
        matrix.fillRect(xPos * sqrSize, yPos * sqrSize, sqrSize, sqrSize, color);
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
                if (index != prevIndex) {
                    clearScreen();
                    prevIndex = index;
                    
                    int i = index;
                    if (isOtherDisplay) {
                        i -= 8;
                    }
                    byte r = 2 + (getRandom()%6);
                    drawSquare(i, COLOR(r,r,r));
                    
                }
                
                
            } break;
            case stateC : {
                
                byte parts = 16;
                byte width = displayW/parts;
                for (int x = 0; x < (index + 1); x++) {
                    byte posx = x - (isOtherDisplay ? (parts/2) : 0);
                    byte hw = width/2;
                    if (posx>=0) {
                        if (index < 8) {
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
        stateC
    };
    
    int index = 0;
    int prevIndex = -999;
    byte offset = 0;
    IntroState state = clear;
    IntroState previousState = clear;
    
    int iMap[16] = {5,9,11,3,8,4,12,0,14,1,6,15,13,2,7,10};
    
    Ticker ticker = Ticker(40);
    Palette rainbow = RainbowPalette();
};


#endif /* Intro_h */
