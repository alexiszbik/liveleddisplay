
#ifndef SQUARES_H
#define SQUARES_H

#include "SquareScene.h"

class Squares : public SquareScene {
    
public:
    Squares(Palette* palette, bool randomMode = false) : SquareScene(8), palette(palette) {
    }
    
    virtual ~Squares() {
        delete palette;
    }
    
public:
    virtual void updateOffsets() override {
        prevPos = pos;
        
        while(pos == prevPos) {
            pos = random(fullSquareCount());
        }
    }
    
    virtual void draw() override {
        byte half = isOtherDisplay ? halfSquareCount() : 0;
        drawSquare(prevPos - half, clearColor());
        byte colorIndex = getRandom() % palette->size;
        drawSquare(pos - half, palette->colors[colorIndex]);
    }
    
private:
    byte pos = 0;
    
    byte prevPos = 0;

    Palette* palette;
};


#endif //SQUARES_H
