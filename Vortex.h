
#ifndef VORTEX_H
#define VORTEX_H

#include "Scene.h"
#include "Palette.h"

#define COLOR_MAX 16

class Vortex : public Scene {

public:

  Vortex(color_t color) : color(color) {
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;
      previousAngle = angle;
      angle = fmod((angle + 0.2), 2.0 * PI);
      c = (c + 1) % COLOR_MAX;
      offset = (offset + 1) % 16;
    }
  }

  void getRotation(float x, float y, float &X, float &Y, float inAngle) {
    float _angle = inAngle; //+ (isOtherDisplay ? PI : 0);
    X = (x - center_x) * cos(_angle) - (y - center_y) * sin(_angle) + center_x;
    Y = (x - center_x) * sin(_angle) + (y - center_y) * cos(_angle) + center_y;
  }

  bool checkPixel(float x, float y) {
    return x > 0 && x < displayW/2 && y > 0 && y < displayH;
  }

  virtual void draw() override {
    matrix.startWrite();
    center_x = isOtherDisplay ? 0 : displayW/2;
    clearScreen();

    color_t _color = matrix.ColorHSV((1535/COLOR_MAX * c), 255, 255, true);

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
  byte c = 0;
  byte offset = 0;
  float previousAngle = 0;
  color_t color;

  byte center_x = 0;
  byte center_y = displayH/2;

};

#endif //VORTEX_H
