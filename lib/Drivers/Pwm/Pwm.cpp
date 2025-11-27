#include "Drivers/Pwm/Pwm.h"

#include "Drivers/Gpio/Gpio.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

Pwm::Pwm(int pin) {
  _pin = pin;
  _pwm_gpio = std::make_unique<Gpio>(_pin);
  _pwm_gpio->SetMode(Gpio::PWM);
  _slice_num = pwm_gpio_to_slice_num(_pin);
}

void Pwm::Enable() { pwm_set_enabled(_slice_num, true); }

Pwm::~Pwm() { pwm_set_enabled(_slice_num, false); }

void Pwm::SetClockDivider(float divider) {
  pwm_set_clkdiv(_slice_num, divider);
}

void Pwm::SetWrap(int wrap) {
  _wrap = wrap;
  pwm_set_wrap(_slice_num, wrap);
}

void Pwm::SetDuty(int duty_percent) {
  int level = (_wrap + 1) * duty_percent / 100;
  pwm_set_chan_level(_slice_num, pwm_gpio_to_channel(_pin), level);
}
