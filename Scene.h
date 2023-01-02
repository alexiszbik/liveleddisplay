
#ifndef SCENE_H
#define SCENE_H

#include "Ticker.h"

class Scene {
  public:

    virtual ~Scene() {
    }
  	virtual void tick(bool state) {};
    virtual void midiNote(byte noteValue) {};   

  	void prepareFrame() {
    	initFrame();
    	needRefresh = true;
  	}

  	virtual void showFrame(bool _isOtherDisplay) {
      
      if (isOtherDisplay != _isOtherDisplay) {
        initFrame();
        needRefresh = true;
        isOtherDisplay = _isOtherDisplay;
      }
    
  		if (needRefresh) {
  			draw();
  			needRefresh = false;
  		}
  	}

  protected:
  	void initFrame() {
    	clearScreen();
   		matrix.setCursor(0, 0);
  	}

  	virtual void draw() = 0;
  	

  protected:
  	bool needRefresh = true;
    bool isOtherDisplay = false;

};


class TickerScene : public Scene {
  public:

    virtual ~TickerScene() {
      delete ticker;
    }

  protected:
    Ticker *ticker = new Ticker(20);

};


#endif //SCENE_H
