#pragma once
#ifdef PC_SIMULATOR
#include <SDL.h>
#endif

class Gpio {
 public:
  enum Direction { INPUT, OUTPUT };
  enum Mode { SPI = 1, UART = 2, PWM = 4, SIO = 5 };
  Gpio(int pin, Direction direction = OUTPUT, Mode mode = SIO, bool pullup = false);
  ~Gpio();
  void SetMode(Mode mode);
  void Write(bool value);
  bool Read() const;

#ifdef PC_SIMULATOR
  static void SetSimulatedKey(int pin, SDL_Scancode key);
#endif

 private:
  int _pin;
};
