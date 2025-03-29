
#ifndef LASERS_H
#define LASERS_H

#include "Scene.h"
#include "Palette.h"

#define MEMORY_SIZE 8

class Lasers : public Scene {

public:

    struct LaserMemory {
        byte start = 0; 
        byte end = 0;
        uint16_t color = 0;

        void draw() {
            matrix.drawLine(start, 0, end, 16, color);
            matrix.drawLine(start + 1 , 0, end + 1, 16, color);
        }
    };

    Lasers()  {
        
    }
    virtual ~Lasers() {
    }

public:
    virtual void tick(bool state) override {
        if (state)  {
            setNeedsRefresh();
        }
    }

    virtual void draw() override {
        clearScreen();

        memory[memIdx].color = HSV(random(1535), 255, 255);
        memory[memIdx].start = random(displayW);
        memory[memIdx].end = (random(displayW) + 16) % displayW;

        memIdx = (memIdx + 1) % MEMORY_SIZE;

        for (byte i = memIdx; i < (MEMORY_SIZE + memIdx); i++) {
            memory[i % MEMORY_SIZE].draw();
        }
    }

private:
    byte offset = 0;
    LaserMemory memory[MEMORY_SIZE];
    byte memIdx = 0;

};

#endif //CIRCLES_H
