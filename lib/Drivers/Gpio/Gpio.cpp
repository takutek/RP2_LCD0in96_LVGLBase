#include "Drivers/Gpio/Gpio.h"

#include "hardware/gpio.h"

Gpio::Gpio(int pin, Direction direction, Mode mode, bool pullup) {
  _pin = pin;
  gpio_init(_pin);
  if (direction == OUTPUT) {
    gpio_set_dir(_pin, GPIO_OUT);
  } else {
    gpio_set_dir(_pin, GPIO_IN);
    if (pullup) {
      gpio_pull_up(_pin);
    }
  }
  SetMode(mode);
}

Gpio::~Gpio() { gpio_deinit(_pin); }

void Gpio::SetMode(Mode mode) {
  if (mode == SPI) {
    gpio_set_function(_pin, GPIO_FUNC_SPI);
  } else if (mode == UART) {
    gpio_set_function(_pin, GPIO_FUNC_UART);
  } else if (mode == PWM) {
    gpio_set_function(_pin, GPIO_FUNC_PWM);
  } else {  // SIO
            // gpio_set_function(_pin, GPIO_FUNC_SIO);
  }
}

void Gpio::Write(bool value) { gpio_put(_pin, value); }

bool Gpio::Read() const { return gpio_get(_pin); }
