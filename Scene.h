
#ifndef SCENE_H
#define SCENE_H

#include "Ticker.h"
#include "ColorsAndMatrix.h"

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

  	virtual void showFrame() {
      
  		if (needRefresh) {
  			draw();
  			needRefresh = false;
  		}
  	}

  protected:
    void initCursor() {
      matrix.setCursor(0, 0);
    }

  	void initFrame() {
      clearScreen();
      initCursor();
  	}

    int getRandom() {
      return random(1000);
    }

    void setNeedsRefresh() {
      needRefresh = true;
    }

  	virtual void draw() = 0;
  	

  protected:
  	bool needRefresh = true;
};

class AutoRefreshedScene : public Scene {
  public:
  virtual void tick(bool state) override {
    if (state)  {
      needRefresh = true;
      updateOffsets();
    }
  }

  virtual void updateOffsets() {};
};

class TickerScene : public Scene {
  public:

  virtual void showFrame() {
    Scene::showFrame();
    
    if (ticker.checkTime()) {
      needRefresh = true;
    }
  }

  protected:
    Ticker ticker = Ticker(20);

};

struct VuState {
  bool vuUp = false;
  float vuSize = 0;

  void reset() {
    vuUp = true;
    vuSize = 0;
  }
};


#endif //SCENE_H
