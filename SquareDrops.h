
#ifndef SQUARE_DROPS_H
#define SQUARE_DROPS_H

#include "SquareScene.h"

class SquareDrops : public SquareScene {
    
public:
    SquareDrops(Palette* palette, bool mode) : SquareScene(4), palette(palette), mode(mode) {
        colorCount = palette->size;
        initialize();
    }
    
    void initialize() {
        if (mode) {
            for (byte i = 0; i < halfSquareCount(); i++) {
                states[i] = getRandom() % (colorCount + 1);
            }
        } else {
            for (byte i = 0; i < halfSquareCount(); i++) {
                states[i] = colorCount;
            }
        }
    }
    
    virtual ~SquareDrops() {
        delete palette;
    }
    
public:
    virtual void updateOffsets() override {
        if (mode) {
            if (isOtherDisplay) {
                randomSeed(5555);
            }
            
            for (byte i = 0; i < halfSquareCount(); i++) {
                states[i] = (states[i] + 1) % (colorCount + (getRandom() % 10));
            }
        } else {
            pos = (halfSquareCount() + (pos + 1 * (isOtherDisplay ? -1 : 1))) % halfSquareCount();
            
            for (byte i = 0; i < halfSquareCount(); i++) {
                if (i == pos) {
                    states[i] = 0;
                } else {
                    states[i] = (states[i] + 1);
                }
            }
        }
    }
    
    virtual void draw() override {
        
        for (byte index = 0; index < halfSquareCount(); index++) {
            byte colorIndex = states[index];
            color_t color = colorIndex >= colorCount ? clearColor() : palette->colors[colorIndex];
            drawSquare(index, color);
        }
    }
    
    
private:
    byte colorCount;
    byte states[32];
    
    Palette* palette;
    
    byte pos = 0;
    
    bool reInit = false;
    bool mode = false;
};

#endif //SQUARE_DROPS_H
