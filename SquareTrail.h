
#ifndef SQUARE_TRAIL_H
#define SQUARE_TRAIL_H

#include "SquareScene.h"

class SquareTrail : public SquareScene {
    
public:
    SquareTrail(Palette* palette) : SquareScene(4), palette(palette) {
        trailLength = palette->size;
        posMax = halfSquareCount();
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
            drawSquare(p, color, false);
        }
    }
    
private:
    int direction() {
        return (isOtherDisplay ? -1 : 1);
    }
    
private:
    byte trailLength;
    
    byte pos = 0;
    
    byte posMax;
    
    Palette* palette;
};

#endif //SQUARE_TRAIL_H
