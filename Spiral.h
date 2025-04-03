

#ifndef SPIRAL_H
#define SPIRAL_H

#include "Scene.h"
#include "Palette.h"

class Spiral : public Scene {
    
public:
    
    Spiral() {
        for (int y = 0; y < displayH; y++) {
            float dy = y - centerY;
            float dy2 = dy * dy;

            for (int x = 0; x < displayW; x++) {
                float dx = x - centerX;
                
                float r = sqrtApprox(dx * dx + dy2);
                float theta = fastAtan2(dy, dx);

                rArray[x][y] = r;
                thetaArray[x][y] = theta;
            }
        }
    }
    
    float sqrtApprox(float x) {
        union { int i; float x; } u;
        u.x = x;
        u.i = (1 << 29) + (u.i >> 1) - (1 << 22);
        return u.x;
    }

    float fastFmodf(float a, float b) {
        int n = a / b;        // Divise a par b et prend la partie entière
        return a - n * b;     // Soustrait le multiple de b de a
    }

    float fastAtan2(float y, float x) {
        float abs_y = (y < 0.f) ? -y : y;
        abs_y += 1e-10;
        
        float r, angle;
        if (x >= 0) {
            r = (x - abs_y) / (x + abs_y);
            angle = M_PI / 4.f;
        } else {
            r = (x + abs_y) / (abs_y - x);
            angle = 3.f * M_PI / 4.f;
        }
        angle += (0.1963f * r * r - 0.9817f) * r;
        return (y < 0.f) ? -angle : angle;
    }

    void drawWhirlpool() {
        
      for (int y = 0; y < displayH; y++) {

            for (int x = 0; x < displayW; x++) {
                
                float r = rArray[x][y];
                float theta = thetaArray[x][y];
                
                theta += r * 0.3f + timeOffset;

                //int colorValue = (int)(127.5 * (1 + sin(theta)));
                int hue = (int)((theta / M_PI) * 127.5f + 127.5f) % 256;

                /*
                int red = colorValue;
                int g = 255 - colorValue;
                int b = 128;
                */
                //matrix.drawPixel(x, y, COLOR((red/255.0)*7, (g/255.0)*7, (b/255.0)*7));
                matrix.drawPixel(x, y, HSV(hue*6, 255, 255));
                //byte c = hue/256.f * 7;
                //matrix.drawPixel(x, y, COLOR(c,0,0));
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
        timeOffset += 0.34;
        timeOffset = fastFmodf(timeOffset, 2*M_PI);
    }
    
    
    
    
private:
    float timeOffset = 0;
    float thetaArray[displayW][displayH];
    float rArray[displayW][displayH];

    float centerX = displayW / 2.f;
    float centerY = displayH / 2.f;
    
};

#endif //NIGHTSKY_H


