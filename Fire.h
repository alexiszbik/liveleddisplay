

#ifndef FIRE_H
#define FIRE_H

#include "Scene.h"
#include "Palette.h"

class Fire : public Scene {
    
public:
    
    Fire() {
        for (int y = 0; y < displayH; y++) {
            for (int x = 0; x < displayW; x++) {
                heat[x][y] = 0;
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
        
        for (int x = 0; x < displayW; x++) {
            // Ajouter une nouvelle "chaleur" aléatoire en bas
            heat[x][displayH - 1] = getRandom()%95 + 160;
        }
        
        for (int y = 0; y < displayH - 1; y++) {
            for (int x = 0; x < displayW; x++) {
                // Faire remonter la chaleur avec une légère diffusion
                heat[x][y] = (heat[x][y + 1] + heat[(x + 1) % displayW][y + 1] + heat[(x - 1 + displayW) % displayW][y + 1]) / 3.4;
            }
        }
        
        // Convertir le tableau "heat" en couleurs
        for (int y = 0; y < displayH; y++) {
            for (int x = 0; x < displayW; x++) {
                int colorHeat = heat[x][y]; // Intensité de chaleur
                byte r, g, b;
                if (colorHeat > 170) {
                    r = 255;
                    g = 255;
                    b = (colorHeat - 170) * 3;
                } else if (colorHeat > 85) {
                    r = 255;
                    g = (colorHeat - 85) * 3;
                    b = 0;
                } else {
                    r = colorHeat * 3;
                    g = 0;
                    b = 0;
                }
                
                r = round((r / 255.0) * 7.0);
                g = round((g / 255.0) * 7.0);
                b = round((b / 255.0) * 7.0);
                
                matrix.drawPixel(x, y, COLOR(r, g, b));
                
            }
        }
        
        matrix.endWrite();
    }
    
    
    
    
private:
    byte heat[displayW][displayH];
    
};

#endif //FIRE_H
