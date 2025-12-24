#include <thread>

#include "Drivers/Thread/Thread.h"
#include "Drivers/Timer/Timer.h"

class Thread::Impl {
 public:
  Impl() : _running(false) {}

  ~Impl() { _thread.detach(); }

  bool Start(std::function<void()> func) {
    if (_running || _thread.joinable()) {
      return false;
    }

    _running = true;
    _thread = std::thread([this, func]() {
      func();
      _running = false;
    });

    return true;
  }

 private:
  std::thread _thread;
  bool _running;
};

Thread::Thread() : _impl(std::make_unique<Impl>()) {}

Thread::~Thread() = default;

bool Thread::Start(std::function<void()> func) { return _impl->Start(func); }
