#ifndef AUTO_VU_H
#define AUTO_VU_H

#include "BigVu.h"

class AutoVu : public BigVu {
public:
  AutoVu(Palette* palette) : BigVu(palette,0,8,BigVu::verticalMirrored) {
  }

  virtual float getRiseAmount() override {
    return 0.75f;
  }

  virtual void tick(bool state) override {
    if (state)  {
      vuStates[autoTriggerIdx].reset();
      autoTriggerIdx = (autoTriggerIdx + 1) % noteCount;
    }
  }

private:
  byte autoTriggerIdx = 0;
};

#endif //AUTO_VU_H