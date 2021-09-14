
#ifndef SCENE_H

#define SCENE_H

class Scene {
  public:

  	virtual void tick(bool state) {};

  	void prepareFrame() {
    	initFrame();
    	needRefresh = true;
  	}

  	void showFrame(bool _isOtherDisplay) {
      
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


#endif //SCENE_H
