#ifndef SCENE_H
#define SCENE_H

class Scene {
  public:

  	virtual void tick(bool state) = 0;

  	void prepareFrame() {
    	initFrame();
    	needRefresh = true;
  	}

  	void showFrame(bool isOtherDisplay) {
  		if (needRefresh) {
  			draw(isOtherDisplay);
  			needRefresh = false;
  		}
  	}

  protected:
  	void initFrame() {
    	clearScreen();
   		matrix.setCursor(0, 0);
  	}

  	virtual void draw(bool isOtherDisplay) = 0;
  	

  protected:
  	bool needRefresh = true;

};


#endif //SCENE_H
