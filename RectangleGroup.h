
#ifndef RECTANGLE_GROUP_H
#define RECTANGLE_GROUP_H

#define RECT_COUNT 4

class RectangleGroup : public AutoRefreshedScene {
    
    struct Rectangle  {
        Rectangle(Palette* palette, byte ratio = 1, byte position = 0) : position(position), ratio(ratio), palette(palette)  {
            rectCount = palette->size;
            offset = position*2;
        }
        
        void tick(bool state) {
            if (state)  {
                hPos = ((hPos + 1) + maxHPos) % (maxHPos);
            }
        }
        
        void draw(bool isOtherDisplay) {
            
            for (byte i = 0; i < rectCount; i++) {
                
                byte p = ((hPos + offset - i) + maxHPos) % maxHPos;
                
                color_t color = i == rectCount ? clearColor() : palette->colors[i];
                
                int x = p + (displayW/ratio)*position - (isOtherDisplay ? displayW/2 : 0);
                
                byte w = displayW/ratio - p*2;
                
                matrix.drawRect(x, p, w, displayH - p*2, color);
            }
        }
        
        byte rectCount;
        byte hPos = 0;
        
        const byte maxHPos = (displayH/2);
        byte position = 0;
        byte ratio = 1;
        byte offset = 0;
        
        Palette* palette; //Palette is a reference here, we don't delete it
        
    };
  
public:
  RectangleGroup(Palette* palette) : palette(palette)  {
    for (byte i = 0; i < RECT_COUNT; i++) {
       rectangles[i] = new Rectangle(palette, RECT_COUNT, i);
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
    AutoRefreshedScene::tick(state);
    for (byte i = 0; i < RECT_COUNT; i++) {
       rectangles[i]->tick(state);
    }
  }

  virtual void draw() override {
    for (byte i = 0; i < RECT_COUNT; i++) {
      rectangles[i]->draw(isOtherDisplay);
    }
  }


private:
  Rectangle* rectangles[RECT_COUNT];

  Palette* palette;

};

#endif //RECTANGLE_GROUP_H
