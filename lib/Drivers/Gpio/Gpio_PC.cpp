#include <SDL.h>

#include <unordered_map>

#include "Board/BoardConfig/KeyMapping_PC.h"
#include "Drivers/Gpio/Gpio.h"

static std::unordered_map<int, SDL_Scancode> g_pin_key_map;

Gpio::Gpio(int pin, Mode mode, Direction direction) {
  (void)mode;
  (void)direction;
  _pin = pin;
  auto it = KeyMapping::PIN_TO_KEY.find(pin);
  g_pin_key_map[pin] =
      (it != KeyMapping::PIN_TO_KEY.end()) ? it->second : SDL_SCANCODE_SPACE;
}

Gpio::~Gpio() { g_pin_key_map.erase(_pin); }

void Gpio::SetMode(Mode mode) { (void)mode; }

void Gpio::Write(bool value) { (void)value; }

bool Gpio::Read() const {
  SDL_PumpEvents();
  const uint8_t* state = SDL_GetKeyboardState(nullptr);
  auto it = g_pin_key_map.find(_pin);
  if (it == g_pin_key_map.end()) return false;
  SDL_Scancode scancode = it->second;
  return state[scancode] != 0;
}

void Gpio::SetSimulatedKey(int pin, SDL_Scancode key) {
  g_pin_key_map[pin] = key;
}
