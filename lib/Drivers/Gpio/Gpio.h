#pragma once

class Gpio {
 public:
  enum Direction { INPUT, OUTPUT };
  enum Mode { SPI = 1, UART = 2, PWM = 4, SIO = 5 };
  Gpio(int pin, Mode mode = SIO, Direction direction = OUTPUT);
  ~Gpio();
  void SetMode(Mode mode);
  void Write(bool value);

 private:
  int _pin;
};
