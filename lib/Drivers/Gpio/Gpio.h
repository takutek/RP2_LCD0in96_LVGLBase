#pragma once

class Gpio {
public:
    enum Direction {
        INPUT,
        OUTPUT
    };
    enum Mode {
        SPI = 1,
        PWM = 4
    };
    Gpio(int pin, Direction direction = OUTPUT);
    ~Gpio();
    void SetMode(Mode mode);
    void Write(bool value);

private:
    int _pin;
};
