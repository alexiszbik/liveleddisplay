#ifndef TICKER_H
#define TICKER_H

class Ticker {
  public:
  
  Ticker(unsigned long msTime) {
    this->msTime = msTime;
  }

  bool checkTime() {
    bool result = false;
    thisTime = millis() % msTime;
    if (previousTime > thisTime) {
      result = true;
    }
    previousTime = thisTime;
    return result;
  }

private:
  unsigned long msTime = 0;
  unsigned long thisTime = 0;
  unsigned long previousTime = 9999; 
};

#endif //TICKER_H
