#include "Tasks/ForegroundTask/ForegroundTask.h"

#include <cstring>

#include "Drivers/Timer/Timer.h"
#include "LvglPort/LvglPort.h"
#include "Screen/Scale.h"

ForegroundTask::ForegroundTask(Fifo& fifo) : _fifo(fifo) {}

int ForegroundTask::Run() {
  std::unique_ptr<LvglPort> lvglPort = std::make_unique<LvglPort>();
  std::unique_ptr<Scale> scale = std::make_unique<Scale>();

  scale->Create();

  while (true) {
    uint32_t bits = _fifo.pop(false);
    float temp = 0.0f;
    std::memcpy(&temp, &bits, sizeof(bits));
    scale->Update(&temp);
    SleepMs(1000);
  }
  return 0;
}
