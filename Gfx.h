
#ifndef GFX_H
#define GFX_H

#include "Scene.h"
#include "GfxRes.h"

class Gfx : public Scene {
    
public:
    enum EGfxMode {
        gfxMode_normal,
        gfxMode_plain,
        gfxMode_plainWithContour,
        gfxMode_inverted,
        gfxMode_invertedWithContour
    };
    
public:
    Gfx(Palette* palette, GfxEnum gfxEnum, EGfxMode mode = gfxMode_normal, bool yMove = false, bool colorMove = false) : palette(palette), yMove(yMove), colorMove(colorMove), mode(mode) {
        switch (gfxEnum) {
            case gfx_hearth :
                for (byte i = 0; i < 16; i++) {
                    buf[i] = pgm_read_word(&hearth[i]);
                }
                break;
            case gfx_star :
                for (byte i = 0; i < 16; i++) {
                    buf[i] = pgm_read_word(&star[i]);
                }
                break;
        }
    }
    
    virtual ~Gfx() {
        delete palette;
    }
    
public:
    virtual void tick(bool state) override {
        if (state)  {
            setNeedsRefresh();
            
            offset = (offset + 1) % 32;
            yOffset = (offset + 1) % 16;
            cOffset = (cOffset + 1) % palette->size;
        }
    }
    
    virtual void draw() override {
        clearScreen();
        matrix.startWrite();
        
        //top
        byte maxW = 16;
        
        const byte w = 16;
        const byte h = 16;
        
        bool fillH = false;
        bool contour = false;
        bool inverted = false;
        
        if (mode == 1) {
            fillH = true;
            contour = false;
            inverted = false;
        }
        if (mode == 2) {
            fillH = true;
            contour = true;
            inverted = false;
        }
        if (mode == 3) {
            fillH = true;
            contour = false;
            inverted = true;
        }
        if (mode == 4) {
            fillH = true;
            contour = true;
            inverted = true;
        }
        
        for (byte j = 0; j < h; j++) {
            if (inverted) {
                matrix.drawLine(0, j, displayW, j, palette->colors[0]);
            } else {
                if (buf[j] == 0) {
                    continue;
                }
            }
            
            bool fill = false;
            
            for (byte i = 0; i < w; i++) {
                
                color_t c;
                bool state = ((buf[j] & (1<<i)) == (1<<i));
                if (inverted) {
                    
                    c = (state || fill) ? COLOR(0,0,0) : palette->colors[0];
                    //c = (state || fill) ? COLOR(0,0,0) : palette->colors[cOffset];
                   
                    if (state) {
                        c = contour ? COLOR(7,7,7) : c;
                    }
                } else {
                    if (!fill && !state) {
                        continue;
                    }
                    
                    if (palette->size == 1) {
                        c = palette->colors[0];
                    } else {
                        byte index = ((i+j) * palette->size / (h+w)) + (colorMove ? cOffset : 0); //?;
                        index = index % palette->size;
                        c = palette->colors[index];
                    }
                    
                    if (state) {
                        c = contour ? COLOR(7,7,7) : c;
                    }
                }
                
                for (int z = 0; z < 4; z++) {
                    int x = i + maxW*z + offset;
                    byte y = j;
                    
                    if (yMove) {
                        y = (z % 2) ? ((j + yOffset) % displayH) : (((j - yOffset) + displayH) % displayH);
                    }
                    
                    matrix.drawPixel(x % displayW, y, c);
                }
                
                if (state && fillH) {
                    bool invert = true;
                    if (i > 0) {
                        bool prevState = ((buf[j] & (1<<(i-1))) == (1<<(i-1)));
                        if (prevState != false) {
                            invert = false;
                        }
                    }
                    if (i < (w-1)) {
                        bool nextState = ((buf[j] & (1<<(i+1))) == (1<<(i+1)));
                        if (nextState != false) {
                            invert = false;
                        }
                    }
                    if (invert) {
                        fill = !fill;
                    }
                }
            }
        }
        
        matrix.endWrite();
    }
    
private:
    Palette* palette;
    
    byte offset = 0;
    byte cOffset = 0;
    byte yOffset = 0;

    bool yMove;
    bool colorMove;
    
    int buf[16];
    
    EGfxMode mode = gfxMode_normal; //0 normal //1 plain //2 plain with contour //3 inverted //4inverted with contour
};

#endif //GFX_H
