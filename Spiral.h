

#ifndef SPIRAL_H
#define SPIRAL_H

#include "Scene.h"
#include "Palette.h"

class Spiral : public Scene {
    
public:
    
    Spiral() {

    }
    
    float sqrtApprox(float x) {
        union { int i; float x; } u;
        u.x = x;
        u.i = (1 << 29) + (u.i >> 1) - (1 << 22);
        return u.x;
    }
    
    float fastAtan2(float y, float x) {
        
        float abs_y = (y < 0) ? -y : y;  // Remplace fabs(y)
        abs_y += 1e-10; // Évite la division par zéro
        
        float r, angle;
        if (x >= 0) {
            r = (x - abs_y) / (x + abs_y);
            angle = M_PI / 4;
        } else {
            r = (x + abs_y) / (abs_y - x);
            angle = 3 * M_PI / 4;
        }
        angle += (0.1963 * r * r - 0.9817) * r;
        return (y < 0) ? -angle : angle;
    }

    // Fonction pour dessiner un tourbillon
    void drawWhirlpool() {
        float centerX = displayW / 2.0;
        float centerY = displayH / 2.0;

        for (int y = 0; y < displayH; y++) {
            float dy = y - centerY;
            float dy2 = dy * dy;
            for (int x = 0; x < displayW; x++) {

                float dx = x - centerX;
                
                float r = sqrtApprox(dx * dx + dy2);
                float theta = fastAtan2(dy, dx);

                theta += r * 0.3 + timeOffset;

                //int colorValue = (int)(127.5 * (1 + sin(theta)));
                int hue = (int)((theta / M_PI) * 127.5 + 127.5) % 256;

                /*
                int red = colorValue;
                int g = 255 - colorValue;
                int b = 128;
                */
                //matrix.drawPixel(x, y, COLOR((red/255.0)*7, (g/255.0)*7, (b/255.0)*7));
                matrix.drawPixel(x, y, HSV(hue*6, 255, 255));
            }
        }
    }

    
public:
    virtual void tick(bool state) override {
        if (state)  {
            setNeedsRefresh();
        }
    }
    
    virtual void draw() override {
        matrix.startWrite();
        drawWhirlpool();
        matrix.endWrite();
        timeOffset += 0.1;
        timeOffset = fmodf(timeOffset,6.28318530718f);
    }
    
    
    
    
private:
    float timeOffset = 0;
    
    int spiralMatrix[displayH][displayW];
    
};

#endif //NIGHTSKY_H


