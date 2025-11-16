#pragma once

class Adc {
public:
    Adc(int channel);
    ~Adc() = default;
    float ReadVoltage();
    static float GetTempFromAdcVoltage(float adc_voltage);
    constexpr static int TEMP_SENSOR_CHANNEL = 4; // QFN-60の場合
private:
    int _channel;
};
