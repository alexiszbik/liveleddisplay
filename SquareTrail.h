
#ifndef SQUARE_TRAIL_H
#define SQUARE_TRAIL_H

#include "SquareScene.h"

class SquareTrail : public SquareScene {
    
public:
    SquareTrail(Palette* palette, bool mirror = true) : SquareScene(4), palette(palette), mirror(mirror) {
        trailLength = palette->size;
        posMax = mirror ? halfSquareCount() : fullSquareCount();
    }
    
    virtual ~SquareTrail() {
        delete palette;
    }
    
    
public:
    virtual void updateOffsets() override {
        pos = ((pos + 1 * direction()) + posMax) % posMax;
    }
    
    virtual void draw() override {
        
        for (byte i = 0; i < (trailLength + 1); i++) {
            color_t color = i == trailLength ? clearColor() : palette->colors[i];
            
            int p = ((pos - i * direction()) + posMax) % posMax;
            int offset = mirror ? 0 : (isOtherDisplay ? (displayHalfW/sqrSize) : 0);
            drawSquare(p - offset, color, !mirror);
        }
    }
    
private:
    int direction() {
        return mirror ? (isOtherDisplay ? -1 : 1) : 1;
    }
    
private:
    byte trailLength;
    
    byte pos = 0;
    
    byte posMax;
    
    Palette* palette;
    bool mirror = false;
};

#endif //SQUARE_TRAIL_H
