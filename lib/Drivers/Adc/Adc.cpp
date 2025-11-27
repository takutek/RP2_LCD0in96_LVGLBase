#include "Drivers/Adc/Adc.h"

#include <mutex>

#include "hardware/adc.h"

static std::once_flag adc_init_flag;

Adc::Adc(int channel) {
  std::call_once(adc_init_flag, []() { adc_init(); });
  _channel = channel;
  if (channel == TEMP_SENSOR_CHANNEL) {
    adc_set_temp_sensor_enabled(true);
  } else {
    adc_gpio_init(channel);
  }
}

float Adc::ReadVoltage() {
  adc_select_input(_channel);
  return static_cast<float>(adc_read()) * AdcConversionFactor;
}
