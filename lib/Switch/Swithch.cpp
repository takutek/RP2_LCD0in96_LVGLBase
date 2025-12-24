#include "Drivers/Gpio/Gpio.h"
#include "Drivers/Switch/Switch.h"

Switch::Switch(int pin, bool active_low) {
  _active_low = active_low;
  _state = State::OFF;
  _gpio = std::make_unique<Gpio>(pin, Gpio::Direction::INPUT);
}

Switch::~Switch() = default;

Switch::State Switch::ReadState() { return _state; }

Switch::State Switch::ReadEvent() {
  State temp = _event;
  _event = State::OFF;
  return temp;
}

Switch::State Switch::UpdateState() {
  if (active_low) {
    pin_state = !_gpio->Read();
  } else {
    pin_state = _gpio->Read();
  }

  if (pin_state) {
    _count++;
    if (_count >= LONG_PRESS_COUNT) {
      _state = State::LongPress;
    } else if (_count >= CONFIRM_COUNT) {
      _state = State::ShortPress;
    }
  } else {
    if (_count >= CONFIRM_COUNT) {
      _event = _state;
      _state = State::OFF;
      _count = 0;
    }
  }
  return _state;
}
