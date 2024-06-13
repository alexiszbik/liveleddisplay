
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Scene.h"
#include "Palette.h"

class Rectangle : public Scene {
    friend class RectangleGroup;
public:
    //ratio : 1,2 or 4
    Rectangle(Palette* palette, byte ratio = 1, byte position = 0) : position(position), ratio(ratio), palette(palette)  {
        rectCount = palette->size;
        offset = position*2;
    }
    
public:
    virtual void tick(bool state) override {
        if (state)  {
            needRefresh = true;
            
            hPos = ((hPos + 1) + maxHPos) % (maxHPos);
        }
    }
    
    virtual void draw() override {
        
        for (byte i = 0; i < (rectCount + 1); i++) {
            
            byte p = ((hPos + offset - i) + maxHPos) % maxHPos;
            
            color_t color = i == rectCount ? clearColor() : palette->colors[i];
            
            int x = p + (displayW/ratio)*position - (isOtherDisplay ? displayW/2 : 0);
            
            byte w = displayW/ratio - p*2;
            
            matrix.drawRect(x, p, w, displayH - p*2, color);
            
        }
    }
    
private:
    byte rectCount;
    byte hPos = 0;
    
    const byte maxHPos = (displayH/2);
    byte position = 0;
    byte ratio = 1;
    byte offset = 0;
    
    Palette* palette; //Palette is a reference here, we don't delete it
    
};

#endif //RECTANGLE_H
