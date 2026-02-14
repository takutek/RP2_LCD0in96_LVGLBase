#pragma once
#include <cstdint>
#include <functional>
#include <memory>

uint64_t GetMillsSinceBoot();
void SleepMs(uint32_t ms);

class Timer {
 public:
  using Callback = std::function<bool()>;

  Timer();
  ~Timer();

  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;
  Timer(Timer&&) = delete;
  Timer& operator=(Timer&&) = delete;

  bool RegisterCallback(Callback&& cb, uint32_t interval_ms);
  bool Cancel();

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};
