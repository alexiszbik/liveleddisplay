
#ifndef STICKS_H
#define STICKS_H

#include "Scene.h"
#include "Palette.h"

class Sticks : public AutoRefreshedScene {
    
public:
    Sticks(Palette* palette, byte width = 2, byte space = 2, byte speed = 2) : width(width), space(space), speed(speed), palette(palette)  {
        colorSize = width + space;
        maxStickCount = palette->size * (colorSize);
    }
    
    virtual ~Sticks() {
        delete palette;
    }
    
public:
    virtual void updateOffsets() override {
        xPos = ((xPos + speed) + maxStickCount) % maxStickCount;
    }
    
    virtual void draw() override {
        
        for (byte d = 0; d < 2; d++) { // mirroring

            for (byte i = 0; i < displayHalfW; i++) {

                byte pos = xPos;
                if (d == 1) {
                    pos = (maxStickCount - pos) % maxStickCount;
                }
            
                byte c = i + pos;
            
                byte cIndex = c % colorSize;
            
                color_t color = 0;

                byte x = i + (d == 1 ? displayHalfW : 0);
            
                if (cIndex == 0) {
            
                    color = palette->colors[c/colorSize % palette->size];
                    matrix.fillRect(x, 0, width, displayH, color);
                } else if (cIndex == width) {
                
                    matrix.fillRect(x, 0, space, displayH, color);
                }
            }
        }
    }
    
private:
    
    byte width;
    byte space;
    byte speed;
    
    byte xPos = 0;
    
    byte maxStickCount;
    byte colorSize;
    
    Palette* palette;
    
};

#endif //STICKS_H
