
#ifndef STARTOUR_H
#define STARTOUR_H

#include "Scene.h"
#include "Palette.h"

#define TRAIL_COUNT 6

class StarTour : public AutoRefreshedScene {
    struct TrailData {
        byte len;
        byte offset;
        
        void increment() {
            offset = (offset + 1) % len;
        }
    };
    
public:
    StarTour() {
        for (byte i = 0; i < TRAIL_COUNT; i++) {
            byte len = 8 + random(10);
            trailData[i].len = len;
            trailData[i].offset = 0;
        }
    }
    
    virtual ~StarTour() {
    }
    
    
public:
    virtual void updateOffsets() override {
        for (byte i = 0; i < TRAIL_COUNT; i++) {
            trailData[i].increment();
        }
    }
    
    color_t grey(byte level) {
        return matrix.Color333(level, level, level);
    }
    
    virtual void draw() override {
        
        matrix.startWrite();
        
        byte midY = displayHalfH;
        float yIncrement = ((float)midY)/((float)width);
        
        float y = 0.f;
        for (byte x = 0; x < width; x++) {
            y = y + yIncrement;
            
            const byte z = TRAIL_COUNT/2;
            
            for (int b = 0; b < z; b++) {
                static float ratio[z] = {0.5f,1.5f,4};
                float dy = y * ratio[b];
                
                for (byte k = 0; k < 2; k++) {
                    byte db = b*2 + k;
                    TrailData* d = &trailData[db];
                    byte colorIndex = ((x + d->offset) % d->len);
                    color_t c = (colorIndex <= 7) ? grey(colorIndex) : clearColor();
                    byte y = k == 0 ? midY + floor(dy) :  midY - 1 - floor(dy);
                    matrix.writePixel(!isOtherDisplay ? width - x : x, y ,c);
                }
            }
        }
        
        matrix.endWrite();
    }
    
    
public:
    byte offset = 0;
    const byte width = displayHalfW;
    
    TrailData trailData[TRAIL_COUNT];
    
};

#endif //STARTOUR_H
