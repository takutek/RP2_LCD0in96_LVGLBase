#include <mutex>
#include "Drivers/Adc/Adc.h"
#include "hardware/adc.h"

static std::once_flag adc_init_flag;

namespace {
    constexpr float AdcConversionFactor = 3.3f / ((1 << 12) - 1);
    constexpr float TempCompFactor = -5.0f;
}

Adc::Adc(int channel)
{
    std::call_once(adc_init_flag, [](){
        adc_init();
    });
    _channel = channel;
    if(channel == TEMP_SENSOR_CHANNEL) {
        adc_set_temp_sensor_enabled(true);
    }
    else {
        adc_gpio_init(channel);
    }
}

float Adc::ReadVoltage()
{
    adc_select_input(_channel);
    return static_cast<float>(adc_read()) * AdcConversionFactor;
}

float Adc::GetTempFromAdcVoltage(float adc_voltage)
{
    return 27.0f - (adc_voltage - 0.706f) / 0.001721f + TempCompFactor;
}
