#include "Tasks/BackgroundTask/BackgroundTask.h"

#include <atomic>
#include <cstring>

#include "Board/BoardConfig/BoardConfig.h"
#include "Drivers/Adc/Adc.h"
#include "Drivers/Thread/Thread.h"
#include "Drivers/Timer/Timer.h"
#include "Switch/Switch.h"

class BackgroundTask::Impl {
 public:
  explicit Impl(Fifo& fifo)
      : _fifo(fifo),
        _adc(std::make_unique<Adc>(Adc::TEMP_SENSOR_CHANNEL)),
        _sw(std::make_unique<Switch>(PinConfig::SWITCH_PIN, true)),
        _timer(std::make_unique<Timer>()),
        _stopFlag(false) {}

  void UpdateSwitch() { _sw->UpdateState(); }

  void Run() {
    _timer->RegisterCallback(
        [this]() -> bool {
          UpdateSwitch();
          return true;
        },
        BoardConfig::SW_READ_INTERVAL_MS);

    while (!_stopFlag.load()) {
      Switch::State event = _sw->ReadEvent();
      uint32_t event_bits = 0;
      if (event != Switch::State::OFF) {
        event_bits = (static_cast<uint32_t>(event) << 30);
      }
      (void)event_bits;
      if (_fifo.can_be_pushed()) {
        const float temp = Adc::GetTempFromAdcVoltage(_adc->ReadVoltage());
        int16_t temp_int = static_cast<int16_t>(temp * 100);
        uint32_t temp_bits = static_cast<uint16_t>(temp_int) & 0xFFFF;
        uint32_t message = temp_bits;
        _fifo.push(message, false);
      }
      SleepMs(1000);
    }
  }

  void RequestStop() { _stopFlag.store(true); }

 private:
  Fifo& _fifo;
  std::unique_ptr<Adc> _adc;
  std::unique_ptr<Switch> _sw;
  std::unique_ptr<Timer> _timer;
  std::atomic<bool> _stopFlag{false};
};

BackgroundTask::BackgroundTask(Fifo& fifo) : _fifo(fifo) {
  _impl = std::make_unique<Impl>(_fifo);
  _thread = std::make_unique<Thread>();
}

BackgroundTask::~BackgroundTask() { RequestStop(); }

bool BackgroundTask::Start() {
  return _thread->Start([this]() { _impl->Run(); });
}

void BackgroundTask::RequestStop() { _impl->RequestStop(); }
