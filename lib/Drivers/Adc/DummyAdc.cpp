#include "Drivers/Adc/Adc.h"

Adc::Adc(int channel) { _channel = channel; }

float Adc::ReadVoltage() {
  static float voltage = 0.69f;
  voltage += 0.01f;
  if (voltage > 0.74f) {
    voltage = 0.69f;
  }
  return voltage;
}
