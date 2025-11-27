#pragma once
#include <memory>

// Forward declaration
class Gpio;

class Pwm {
 public:
  Pwm(int pin);
  ~Pwm();
  void Enable();
  void SetClockDivider(float divider);
  void SetWrap(int wrap);
  void SetDuty(int duty_percent);

 private:
  int _pin;
  int _slice_num;
  int _wrap;
  std::unique_ptr<Gpio> _pwm_gpio;
};
