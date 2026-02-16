#include "Switch/Switch.h"

#include "Drivers/Gpio/Gpio.h"

Switch::Switch(int pin, bool active_low)
    : _gpio(
          std::make_unique<Gpio>(pin, Gpio::Direction::INPUT, Gpio::SIO, true)),
      _count(0),
      _state(State::OFF),
      _event(State::OFF),
      _active_low(active_low) {}

Switch::~Switch() = default;

Switch::State Switch::ReadState() { return _state; }

Switch::State Switch::ReadEvent() {
  State temp = _event;
  _event = State::OFF;
  return temp;
}

void Switch::UpdateState() {
  const bool pin_state = _active_low ? !_gpio->Read() : _gpio->Read();

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
}
