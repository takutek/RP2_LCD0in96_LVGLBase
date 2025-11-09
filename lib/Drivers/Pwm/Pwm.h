#pragma once
#include <memory>
#include "Drivers/Gpio/Gpio.h"

class Pwm {
public:
    Pwm(int pin);
    ~Pwm();
    void Enable();
    void SetClockDivider(float divider);
    void SetWrap(int wrap);
    void SetFrequency(int frequency);
    void SetLevel(int level);
private:
    int _pin;
    int _slice_num;
    int _divider;
    int _wrap;
    std::unique_ptr<Gpio> _pwm_gpio;
};
