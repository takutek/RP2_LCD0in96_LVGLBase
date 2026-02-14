#include <windows.h>

#include "Drivers/Timer/Timer.h"

uint64_t GetMillsSinceBoot() { return GetTickCount64(); }

void SleepMs(uint32_t ms) { Sleep(ms); }

class Timer::Impl {};

Timer::Timer() : impl_(std::make_unique<Impl>()) {}

Timer::~Timer() = default;

bool Timer::RegisterCallback(Callback&& cb, uint32_t interval_ms) {
  return true;
}

bool Timer::Cancel() { return true; }
