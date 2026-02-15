#pragma once

#include <memory>

#include "Fifo/Fifo.h"

class Thread;

class BackgroundTask {
 public:
  explicit BackgroundTask(Fifo& fifo);
  ~BackgroundTask();

  BackgroundTask(const BackgroundTask&) = delete;
  BackgroundTask& operator=(const BackgroundTask&) = delete;
  BackgroundTask(BackgroundTask&&) = delete;
  BackgroundTask& operator=(BackgroundTask&&) = delete;

  bool Start();
  void RequestStop();

 private:
  Fifo& _fifo;
  class Impl;
  std::unique_ptr<Impl> _impl;
  std::unique_ptr<Thread> _thread;
};
