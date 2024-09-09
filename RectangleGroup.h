
#ifndef RECTANGLE_GROUP_H
#define RECTANGLE_GROUP_H

#define RECT_COUNT 4

class RectangleGroup : public AutoRefreshedScene {
    
    struct Rectangle  {
        Rectangle(byte position = 0) : position(position)  {
            offset = position*2;
        }
        
        void tick(bool state) {
            if (state)  {
                hPos = ((hPos + 1) + maxHPos) % (maxHPos);
            }
        }
        
        void draw(Palette* palette) {
            
            byte size = palette->size;
            
            for (byte i = 0; i < (size + 1); i++) {
                
                byte p = ((hPos + offset - i) + maxHPos) % maxHPos;
                
                color_t color = i == size ? clearColor() : palette->colors[i];
                
                int x = p + (displayW/RECT_COUNT)*position;
                
                byte w = displayW/RECT_COUNT - p*2;
                
                matrix.drawRect(x, p, w, displayH - p*2, color);
            }
        }
    
        byte hPos = 0;
        
        const byte maxHPos = (displayH/2);
        byte position = 0;
        byte offset = 0;
        
    };
  
public:
  RectangleGroup(Palette* palette) : palette(palette)  {
    for (byte i = 0; i < RECT_COUNT; i++) {
       rectangles[i] = new Rectangle(i);
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
      rectangles[i]->draw(palette);
    }
  }


private:
  Rectangle* rectangles[RECT_COUNT];

  Palette* palette;

};

#endif //RECTANGLE_GROUP_H
