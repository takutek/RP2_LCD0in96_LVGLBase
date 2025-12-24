#pragma once

#include <cstdint>
#include <functional>
#include <memory>

class Thread {
 public:
  Thread();
  ~Thread();
  Thread(const Thread&) = delete;
  Thread& operator=(const Thread&) = delete;
  Thread(Thread&&) = delete;
  Thread& operator=(Thread&&) = delete;

  bool Start(std::function<void()> func);

 private:
  class Impl;
  std::unique_ptr<Impl> _impl;
};
