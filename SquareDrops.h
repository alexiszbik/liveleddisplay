
#ifndef SQUARE_DROPS_H
#define SQUARE_DROPS_H

#include "Scene.h"

class SquareDrops : public AutoRefreshedScene {
public:
    enum Mode {
        randDrops,
        trail,
        randomOnce
    };
    
public:
    SquareDrops(Palette* palette, SquareDrops::Mode mode) : sqrSize(mode == randomOnce ? 8 : 4), palette(palette), mode(mode) {
        colorCount = palette->size;
        initialize();
    }
    
    void initialize() {
        switch (mode) {
            case randDrops : {
                for (byte i = 0; i < halfSquareCount(); i++) {
                    states[i] = getRandom() % (colorCount + 1);
                }
            } break;
            case trail : {
                for (byte i = 0; i < halfSquareCount(); i++) {
                    states[i] = colorCount;
                }
            } break;
            case randomOnce : {
                for (byte i = 0; i < fullSquareCount(); i++) {
                    states[i] = colorCount;
                }
            }
        }
    }
    
    virtual ~SquareDrops() {
        delete palette;
    }
    
public:
    virtual void updateOffsets() override {
        
        switch (mode) {
            case randDrops : {
                if (isOtherDisplay) {
                    randomSeed(5555);
                }
                
                for (byte i = 0; i < halfSquareCount(); i++) {
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
                byte newPos = getRandom() % fullSquareCount();
                if (newPos != pos) {
                    states[pos] = colorCount;
                    states[newPos] = getRandom() % colorCount;
                    pos = newPos;
                    std::cout << pos << std::endl;
                }
                
            }
        }
    }
    
    virtual void draw() override {
        
        for (byte index = 0; index < (mode == randomOnce ? fullSquareCount() : halfSquareCount()); index++) {
            byte colorIndex = states[index];
            color_t color = colorIndex >= colorCount ? clearColor() : palette->colors[colorIndex];
            int i = index;
            if (mode == randomOnce && isOtherDisplay) {
                i -= 8;
            }
            drawSquare(i, color);
        }
    }
    
    int fullSquareCount() {
        return (displayW/sqrSize) * (displayH/sqrSize);
    }
    
    int halfSquareCount() {
        return (displayHalfW/sqrSize) * (displayH/sqrSize);
    }
    
    void drawSquare(int index, color_t color, bool fullWidth = false) {
        byte perW = ((fullWidth ? displayW : displayHalfW)/sqrSize);
        byte xPos = index % perW;
        byte yPos = index / perW;
        matrix.fillRect(xPos * sqrSize, yPos * sqrSize, sqrSize, sqrSize, color);
    }
    
    
private:
    byte sqrSize;
    byte colorCount;
    byte states[32];
    
    Palette* palette;
    
    byte pos = 0;

private:
    int mode = randDrops;
};

#endif //SQUARE_DROPS_H
