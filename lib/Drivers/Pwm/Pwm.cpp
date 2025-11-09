#include "Drivers/Pwm/Pwm.h"

#include "hardware/clocks.h"
#include "hardware/pwm.h"

Pwm::Pwm(int pin) {
    _pin = pin;
    _pwm_gpio = std::make_unique<Gpio>(_pin);
    _pwm_gpio->SetMode(Gpio::PWM);
    _slice_num = pwm_gpio_to_slice_num(_pin); 
}

void Pwm::Enable() {
    pwm_set_enabled(_slice_num, true);
}

Pwm::~Pwm() {
    pwm_set_enabled(_slice_num, false);
}

void Pwm::SetClockDivider(float divider) {
    _divider = divider;
    pwm_set_clkdiv(_slice_num, static_cast<float>(_divider));
}

void Pwm::SetWrap(int wrap) {
    _wrap = wrap;
    pwm_set_wrap(_slice_num, wrap);
}

void Pwm::SetFrequency(int frequency) {
    const uint32_t pwm_clock = clock_get_hz(clk_sys) / _divider;
    const uint16_t wrap_value = static_cast<uint16_t>((pwm_clock / frequency) - 1);
    pwm_set_wrap(_slice_num, wrap_value);
}

void Pwm::SetLevel(int level) {
    pwm_set_chan_level(_slice_num, PWM_CHAN_B, level);
}
