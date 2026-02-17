#pragma once

#include <memory>

#include "Drivers/Fifo/Fifo.h"

class LvglPort;

class ForegroundTask {
 public:
  explicit ForegroundTask(Fifo& fifo);
  ~ForegroundTask();

  ForegroundTask(const ForegroundTask&) = delete;
  ForegroundTask& operator=(const ForegroundTask&) = delete;
  ForegroundTask(ForegroundTask&&) = delete;
  ForegroundTask& operator=(ForegroundTask&&) = delete;

  int Run();

 private:
  Fifo& _fifo;
  std::unique_ptr<LvglPort> _lvglPort;
};
