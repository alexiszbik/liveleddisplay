#ifndef SQUARE_SCENE_H
#define SQUARE_SCENE_H

#include "Scene.h"

class SquareScene : public AutoRefreshedScene {
public:
    SquareScene(byte sqrSize) : sqrSize(sqrSize)  {
    }
    
    int fullSquareCount() {
        return (displayW/sqrSize) * (displayH/sqrSize);
    }
    
    int halfSquareCount() {
        return (displayHalfW/sqrSize) * (displayH/sqrSize);
    }
    
    void drawSquare(int index, color_t color, bool fullWidth = false) {
        byte perW = ((fullWidth ? displayW : displayHalfW)/sqrSize);
        byte xPos = index % perW;
        byte yPos = index / perW;
        matrix.fillRect(xPos * sqrSize, yPos * sqrSize, sqrSize, sqrSize, color);
    }
protected:
    byte sqrSize;
};

#endif //SQUARE_SCENE_H
