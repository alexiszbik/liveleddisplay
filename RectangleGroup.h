
#ifndef RECTANGLE_GROUP_H
#define RECTANGLE_GROUP_H

#include "Rectangle.h"

#define RECT_COUNT 4

class RectangleGroup : public Scene {
  
public:
  RectangleGroup(Palette* palette) : palette(palette)  {
    for (byte i = 0; i < RECT_COUNT; i++) {
       rectangles[i] = new Rectangle(palette, true, RECT_COUNT, i, i*2);
    }
  }

  virtual ~RectangleGroup() {
    for (byte i = 0; i < RECT_COUNT; i++) {
       delete rectangles[i];
    }
    delete palette;
  }
  
public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;
    }
    for (byte i = 0; i < RECT_COUNT; i++) {
       rectangles[i]->tick(state);
    }
  }

  virtual void draw() override {
    for (byte i = 0; i < RECT_COUNT; i++) {
      rectangles[i]->isOtherDisplay = isOtherDisplay;
       rectangles[i]->draw();
    }
  }


private:
  Rectangle* rectangles[RECT_COUNT];

  Palette* palette;

};

#endif //RECTANGLE_GROUP_H
