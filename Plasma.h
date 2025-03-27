
        
        //PLASMA
        /*
        for (int y = 0; y < displayH; y++) {
            for (int x = 0; x < displayW; x++) {
                
                int16_t v = (sin(x * 0.1) + sin(y * 0.1) + sin((x + y + plasmaTime) * 0.07)) * 127 + 128;

                matrix.drawPixel(x, y, HSV(v * 6, 255, 255));
               
            }
        }
        */
        //
        
        /*
         r * 0.5    Modifie l’échelle du vortex    0.2 = plus grand, 1.0 = plus serré
         angle * 3.0    Nombre de bras de la spirale    2.0 = moins de spirales, 5.0 = plus
         t * 0.1    Vitesse de rotation    0.05 = lent, 0.2 = rapide
         sin(...) + sin(...)    Complexité des formes    Change les coefficients pour varier les ondulations
         */
        
        
        //PLASMA GRADIENT
        /*
        for (int y = 0; y < displayH; y++) {
                for (int x = 0; x < displayW; x++) {
                    float dx = x - displayW / 2.0;
                    float dy = y - displayH / 2.0;
                    float r = sqrt(dx * dx + dy * dy);  // Distance au centre
                    float angle = atan2(dy, dx);  // Angle en radians
                    float v = sin(r * 0.5 + plasmaTime * 0.1) + sin(angle * 3.0 + plasmaTime * 0.05);
                    uint16_t color = HSV((v * 128 + 128) * 6, 255, 255);
                    matrix.drawPixel(x, y, color);
                }
            }
         */
        
        //TUNEL 3D
        /*
         Variable    Effet    Exemples
         r * 0.3    Taille des anneaux du tunnel    0.2 = plus larges, 0.5 = plus fins
         - t * 0.1    Vitesse du tunnel    -0.05 = lent, -0.2 = rapide
         255 * wave    Intensité des couleurs    Augmenter ou réduire la luminosité
         */
        /*
        for (int y = 0; y < displayH; y++) {
               for (int x = 0; x < displayW; x++) {
                   float dx = x - displayW / 2.0;
                   float dy = y - displayH / 2.0;
                   float r = sqrt(dx * dx + dy * dy);  // Distance au centre
                   float angle = atan2(dy, dx);  // Angle en radians
                   
                   float wave = sin(r * 0.3 - plasmaTime * 0.1) * 0.5 + 0.5;  // Effet d'onde de profondeur
                   uint16_t color = HSV((angle + wave) * 500, 255, 255 * wave);
                   matrix.drawPixel(x, y, color);
                   
                  // matrix.drawPixel(x, y, color);
               }
           }
        */


#ifndef PLASMA_H
#define PLASMA_H

#include "Scene.h"
#include "Palette.h"

#define SIN_TABLE_SIZE 256  // Nombre d'échantillons pour une période complète
#define SIN_AMPLITUDE 127  // Amplitude normalisée du sinus

class Plasma : public SyncScene {
    
public:
    
    Plasma() {
        // Pré-calcul des valeurs de sin dans un tableau
        for (int i = 0; i < SIN_TABLE_SIZE; i++) {
            sinTable[i] = sin(i * (2 * PI / SIN_TABLE_SIZE)) * SIN_AMPLITUDE + SIN_AMPLITUDE;
        }
    }
    
public:
    
    virtual void draw() override {
        matrix.startWrite();
        
        // PLASMA optimisé avec table de sinus
        for (int y = 0; y < displayH; y++) {
            for (int x = 0; x < displayW; x++) {
                // Utilisation du tableau pré-calculé au lieu de sin(x)
                int16_t v = (
                    sinTable[(x * 10) % SIN_TABLE_SIZE] +
                    sinTable[(y * 10) % SIN_TABLE_SIZE] +
                    sinTable[((x + y + plasmaTime) * 7) % SIN_TABLE_SIZE]
                ) / 3;  // Normalisation

                matrix.drawPixel(x, y, HSV(v * 6, 255, 255));
            }
        }

        plasmaTime = (plasmaTime + 1) % SIN_TABLE_SIZE;  // Ajuster la vitesse et boucler

        matrix.endWrite();
    }
    
private:
    long plasmaTime = 0;
    uint8_t sinTable[SIN_TABLE_SIZE];  // Table de sinus précalculée
};

#endif // PLASMA_H



