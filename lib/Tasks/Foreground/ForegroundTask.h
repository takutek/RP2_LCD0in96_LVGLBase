#pragma once

#include "Fifo/Fifo.h"

class ForegroundTask {
 public:
  explicit ForegroundTask(Fifo& fifo);
  ~ForegroundTask() = default;

  ForegroundTask(const ForegroundTask&) = delete;
  ForegroundTask& operator=(const ForegroundTask&) = delete;
  ForegroundTask(ForegroundTask&&) = delete;
  ForegroundTask& operator=(ForegroundTask&&) = delete;

  int Run();

 private:
  Fifo& _fifo;
};
