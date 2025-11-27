#pragma once

class Adc {
 public:
  Adc(int channel);
  ~Adc() = default;
  float ReadVoltage();
  static float GetTempFromAdcVoltage(float adc_voltage) {
    return 27.0f - (adc_voltage - 0.706f) / 0.001721f + TempCompFactor;
  }
  constexpr static int TEMP_SENSOR_CHANNEL = 4;  // QFN-60の場合
 private:
  int _channel;
  constexpr static float AdcConversionFactor = 3.3f / ((1 << 12) - 1);
  constexpr static float TempCompFactor = -5.0f;
};
