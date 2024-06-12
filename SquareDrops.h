
#ifndef SQUARE_DROPS_H
#define SQUARE_DROPS_H

#include "SquareScene.h"

class SquareDrops : public SquareScene {
    
public:
    SquareDrops(Palette* palette) : SquareScene(4), palette(palette) {
        colorCount = palette->size;
        initialize();
    }
    
    void initialize() {
        for (byte i = 0; i < halfSquareCount(); i++) {
            states[i] = getRandom() % (colorCount + 1);
        }
    }
    
    virtual ~SquareDrops() {
        delete palette;
    }
    
public:
    virtual void updateOffsets() override {
        if (isOtherDisplay) {
            randomSeed(5555);
        }
        
        for (byte i = 0; i < halfSquareCount(); i++) {
            states[i] = (states[i] + 1) % (colorCount + random(10));
        }
    }
    
    virtual void draw() override {
        
        if (!reInit && isOtherDisplay) {
            initialize();
            reInit = true;
        }
        
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
    
    bool reInit = false;
};

#endif //SQUARE_DROPS_H
