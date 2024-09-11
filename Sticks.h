
#ifndef STICKS_H
#define STICKS_H

#include "Scene.h"
#include "Palette.h"

class Sticks : public AutoRefreshedScene {
    
public: //ok this is still buggy ...
    Sticks(Palette* palette, byte width = 2, byte space = 2, byte speed = 2) : width(width), space(space), speed(speed), palette(palette)  {
        stickSize = width + space;
        maxStickCount = palette->size * (stickSize);
    }
    
    virtual ~Sticks() {
        delete palette;
    }
    
public:
    virtual void updateOffsets() override {
        xPos[0] = ((xPos[0] + speed) + maxStickCount) % maxStickCount;
        xPos[1] = ((xPos[1] - speed) + maxStickCount) % maxStickCount;
    }
    
    virtual void draw() override {
        
        for (byte d = 0; d < 2; d++) { // mirroring

            for (byte i = 0; i < displayHalfW; i++) {

                byte pos = xPos[d];
            
                byte c = i + pos;
            
                byte cIndex = c % stickSize;
            
                color_t color = 0;

                byte x = i + (d == 1 ? displayHalfW : 0);
            
                if (cIndex == 0) {

                    byte j = 0;
                    if (d == 0) {
                        j = (c/stickSize) % palette->size;
                    }  else {
                        j = ((palette->size - (c/stickSize)) + palette->size) % palette->size;
                    }
            
                    color = palette->colors[j];
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
    
    byte xPos[2] = {0, 0};
    
    byte maxStickCount;
    byte stickSize;
    
    Palette* palette;
    
};

#endif //STICKS_H
