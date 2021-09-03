#ifndef SCENE_H
#define SCENE_H

class Scene {
  public:

  	virtual void tick(bool state) = 0;

  	void prepareFrame() {
    	initFrame();
    	needRefresh = true;
  	}

  	void showFrame() {
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

};

class Squares : public Scene {
public:
	virtual void tick(bool state) override {
		if (state)  {
			needRefresh = true;

  			prevXPos = xPos;
  			prevYPos = yPos;

  			/*
  			xPos = (xPos + 1) % (displayW/size);

  			if (xPos == 0) {
  				yPos = (yPos + 1) % (displayH/size);
  			}*/
  			while(prevXPos == xPos && prevYPos == yPos) {
  				xPos = random(displayW/size);
  				yPos = random(displayH/size);
  			}
		}
  		
  	}

  	virtual void draw() override {
  		matrix.fillRect(prevXPos * size, prevYPos * size , size, size, matrix.Color333(0, 0, 0));
  		matrix.fillRect(xPos * size, yPos * size, size, size, randomColor());
  	}

private:
  	byte size = 8;

  	byte xPos = 0;
  	byte yPos = 0;

  	byte prevXPos = 0;
  	byte prevYPos = 0;
};

#endif //SCENE_H