
#ifndef VORTEX_H
#define VORTEX_H

#include "Scene.h"
#include "Palette.h"

class Vortex : public AutoRefreshedScene {

public:

  Vortex(color_t color) : color(color) {
  }
  
public:
  virtual void updateOffsets() override {
    previousAngle = angle;
    angle = (angle + 0.2);
    if (angle > TWO_PI) {
      angle = 0;
    }
    offset = (offset + 1) % 16;
  }

  void getRotation(float x, float y, float &X, float &Y, float inAngle) {
    float _angle = inAngle; //+ (isOtherDisplay ? PI : 0);
    float s = sin(_angle);
    float c = cos(_angle);
    X = (x - center_x) * c - (y - center_y) * s + center_x;
    Y = (x - center_x) * s + (y - center_y) * c + center_y;
  }

  bool checkPixel(float x, float y) {
    return x > 0 && x < displayW/2 && y > 0 && y < displayH;
  }

  virtual void draw() override {
    matrix.startWrite();
    center_x = isOtherDisplay ? 0 : displayW/2;
    clearScreen();

    color_t _color = matrix.ColorHSV((1535/16 * offset), 255, 255, true);

    for (byte sqr = 0; sqr < 4; sqr++) {
      byte sqSize = 16*sqr + offset;
  
      float x = center_x - sqSize/2;
      float y = center_y - sqSize/2;
      float _x = x + sqSize;
      float _y = y + sqSize;
  
      float vectors[4][2] = {{x,y}, {_x, y}, {_x, _y}, {x,_y}};
  
      for (byte i = 0; i < 4; i++) {
        float X, Y, XX, YY;
        byte nextIndex = (i + 1) % 4;
        getRotation(vectors[i][0], vectors[i][1], X, Y, angle);
        getRotation(vectors[nextIndex][0], vectors[nextIndex][1], XX, YY, angle);
        matrix.drawLine(X, Y, XX, YY, _color);
        
      }
    }
 
    matrix.endWrite();
  }


private:
  float angle = 0;
  byte offset = 0;
  float previousAngle = 0;
  color_t color;

  byte center_x = 0;
  byte center_y = displayHalfH;

};

#endif //VORTEX_H
