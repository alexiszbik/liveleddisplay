
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
        for (byte display = 0; display < 2; display++) {
            for (byte i = 0; i < TRAIL_COUNT; i++) {
                byte len = 8 + random(10);
                trailData[display][i].len = len;
                trailData[display][i].offset = 0;
            }
        }
        
    }
    
    virtual ~StarTour() {
    }
    
    
public:
    virtual void updateOffsets() override {
        for (byte display = 0; display < 2; display++) {
            for (byte i = 0; i < TRAIL_COUNT; i++) {
                trailData[display][i].increment();
            }
        }
    }
    
    color_t grey(byte level) {
        return COLOR(level, level, level);
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
                    for (byte display = 0; display < 2; display++) {
                        TrailData* trailD = &trailData[display][db];
                        byte colorIndex = ((x + trailD->offset) % trailD->len);
                        color_t c = (colorIndex <= 7) ? grey(colorIndex) : clearColor();
                        byte y = k == 0 ? midY + floor(dy) :  midY - 1 - floor(dy);
                        if (display == 0) {
                            matrix.writePixel(width - 1 - x , y ,c);
                        } else {
                            matrix.writePixel(width + x, y ,c);
                        }
                    }
                }
            }
        }
        
        matrix.endWrite();
    }
    
    
public:
    byte offset = 0;
    const byte width = displayHalfW;
    
    TrailData trailData[2][TRAIL_COUNT];
    
};

#endif //STARTOUR_H
