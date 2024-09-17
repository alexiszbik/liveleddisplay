
#ifndef OSC_H
#define OSC_H

#include "Scene.h"

#define NO_VALUE 100

#define START_NOTE 48

#define NOTE_ON_OFF 60

#define VU_H 16
#define VU_W 16

static byte cosArray[64] =
{
    15, 15, 15, 15, 15, 14, 14, 13, 13, 12, 11, 11, 10, 9, 8, 8, 7, 6,
    5, 4, 4, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2,
    2, 3, 4, 4, 5, 6, 7, 7, 8, 9, 10, 11, 11, 12, 13, 13, 14, 14, 15,
    15, 15, 15, 15, 15
};

class WaveData {
public:
    byte buf = 0;
    byte offset = 0;
    byte speed = 1;
    
    void updateOffset() {
        offset = (offset + speed) % displayW;
    }
};

class Osc : public Scene {
    
public:
    Osc(Palette* palette) : palette(palette) {
        waveCount = palette->size;
        waveData = new WaveData[waveCount];
        for (byte w = 0; w < waveCount; w++) {
            waveData[w].speed = (w+1);
        }
    }
    
    virtual ~Osc() {
        delete palette;
        delete[] waveData;
    }
    
public:
    virtual void tick(bool state) override {
        if (state && !squareMode)  {
            setNeedsRefresh();
            for (byte w = 0; w < waveCount; w++) {
                waveData[w].updateOffset();
            }
        }
    }
    
    virtual void midiNote(byte noteValue) override {
        
        if (noteValue >= START_NOTE && noteValue <= (START_NOTE + 3))
        {
            if (!squareMode) {
                needsClear = true;
            }
            squareMode = true;
            squarePosition = noteValue - START_NOTE;
        }
        else if (noteValue == NOTE_ON_OFF) {
            needsClear = true;
            showOsc = false;
            
        } else {
            if (squareMode) {
                needsClear = true;
            }
            squareMode = false;
            showOsc = true;
        }
        setNeedsRefresh();
    }
    
    virtual void draw() override {
        
        if (needsClear) {
            clearScreen();
            needsClear = false;
        }
        
        if (squareMode) {
            if (xSqr >= 0) {
                matrix.fillRect(xSqr, 0, VU_W, VU_H, COLOR(0,0,0));
            }
            
            byte colorIndex = getRandom() % palette->size;
            color_t c = palette->colors[colorIndex];
            
            xSqr = (int)squarePosition * (int)VU_W;
            
            if (xSqr >= 0) {
                matrix.fillRect(xSqr, 0, VU_W, VU_H, c);
            }
            
        } else if (showOsc) {
            
            for (byte i = 0; i < displayW; i++) {
                
                for (byte s = 0; s < waveCount; s++) {
                    byte y = cosArray[(waveData[s].offset + i) % 64];
                    byte prevy = cosArray[(waveData[s].offset + i + (64 - waveData[s].speed)) % 64];
                    
                    matrix.drawPixel(i, prevy, COLOR(0,0,0));
                    waveData[s].buf = y;
                }
                
                for (byte s = 0; s < waveCount; s++) {
                    color_t c = palette->colors[s];
                    matrix.drawPixel(i,  waveData[s].buf, c);
                }
            }
        }
    }
    
private:
    byte waveCount = 0;
    Palette* palette;
    
    bool squareMode = false;
    bool needsClear = false;
    byte squarePosition = 0;
    
    bool showOsc = true;
    
    WaveData* waveData = NULL;
    
    int xSqr = 0;
};


#endif //OSC_H
