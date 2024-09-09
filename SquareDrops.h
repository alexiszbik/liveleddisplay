
#ifndef SQUARE_DROPS_H
#define SQUARE_DROPS_H

#include "Scene.h"

class SquareDrops : public AutoRefreshedScene {
public:
    enum Mode {
        randDrops = 0,
        trail,
        randomOnce,
        wash
    };
    
public:
    SquareDrops(Palette* palette, SquareDrops::Mode mode) : sqrSize(mode == randomOnce ? 8 : 4), palette(palette), mode(mode) {
        colorCount = palette->size;
        initialize();
    }
    
    void initialize() {
        switch (mode) {
            case randDrops : {
                for (byte i = 0; i < fullSquareCount(); i++) {
                    states[i] = getRandom() % (colorCount + 1);
                }
            } break;
            case wash :
            case randomOnce :
            case trail : {
                for (byte i = 0; i < fullSquareCount(); i++) {
                    states[i] = colorCount;
                }
            } break;
        }
    }
    
    virtual ~SquareDrops() {
        delete palette;
    }
    
public:
    virtual void updateOffsets() override {
        
        switch (mode) {
            case randDrops : {
                
                for (byte i = 0; i < fullSquareCount(); i++) {
                    states[i] = (states[i] + 1) % (colorCount + (getRandom() % 10));
                }
            } break;
            case trail : {
                pos = (halfSquareCount() + (pos + 1 * (isOtherDisplay ? -1 : 1))) % halfSquareCount();
                
                for (byte i = 0; i < halfSquareCount(); i++) {
                    if (i == pos) {
                        states[i] = 0;
                    } else {
                        states[i] = (states[i] + 1);
                    }
                }
            } break;
            case randomOnce : {
                byte newPos = pos;
                while (pos == newPos) {
                    newPos = getRandom() % fullSquareCount();
                    states[pos] = colorCount;
                    states[newPos] = getRandom() % colorCount;
                }
                pos = newPos;
            } break;
            case wash : {
                const byte len = 8;
                pos = (pos + 1) % len;
                for (byte i = 0; i < fullSquareCount(); i++) {
                    byte y = (i / 8);
                    if (((i + y) % len) == pos) {
                        states[i] = 0;
                    } else {
                        states[i] = (states[i] + 1);
                    }
                }
                
                
            } break;
        }
    }
    
    virtual void draw() override {
        
        for (byte index = 0; index < fullSquareCount(); index++) {
            byte colorIndex = states[index];
            color_t color = colorIndex >= colorCount ? clearColor() : palette->colors[colorIndex];
            int i = index;
            drawSquare(i, color);
        }
    }
    
    int fullSquareCount() {
        return (displayW/sqrSize) * (displayH/sqrSize);
    }
    
    int halfSquareCount() {
        return (displayHalfW/sqrSize) * (displayH/sqrSize);
    }
    
    void drawSquare(int index, color_t color, bool fullWidth = true) {
        byte perW = ((fullWidth ? displayW : displayHalfW)/sqrSize);
        byte xPos = index % perW;
        byte yPos = index / perW;
        matrix.fillRect(xPos * sqrSize, yPos * sqrSize, sqrSize, sqrSize, color);
    }
    
    
private:
    byte sqrSize;
    byte colorCount;
    byte states[64];
    
    Palette* palette;
    
    byte pos = 0;

private:
    int mode = randDrops;
};

#endif //SQUARE_DROPS_H
