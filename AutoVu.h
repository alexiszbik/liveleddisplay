#ifndef AUTO_VU_H
#define AUTO_VU_H

#include "BigVu.h"

class AutoVu : public BigVu {
public:
  AutoVu(Palette* palette) : BigVu(palette, 0, 16, BigVu::vertical) {
  }

  virtual float getRiseAmount() override {
    return 0.75f;
  }

  virtual void tick(bool state) override {
    if (state)  {
      vuStates[autoTriggerIdx].reset();
      //vuStates[autoTriggerIdx + 8].reset();
      vuStates[15 - autoTriggerIdx].reset();
      autoTriggerIdx = (autoTriggerIdx + 1) % 8;
    }
  }

private:
  byte autoTriggerIdx = 0;
};

#endif //AUTO_VU_H
