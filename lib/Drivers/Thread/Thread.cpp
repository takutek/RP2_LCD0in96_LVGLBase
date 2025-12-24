#include "Drivers/Thread/Thread.h"

#include "pico/multicore.h"

static std::function<void()>* core1_func = nullptr;
static bool core1_running = false;

static void core1_entry() {
  if (core1_func) {
    (*core1_func)();
  }
  core1_running = false;
}

class Thread::Impl {
 public:
  Impl() : _started(false) {}

  ~Impl() {}

  bool Start(std::function<void()> func) {
    if (_started || core1_running) {
      return false;
    }

    _func = func;
    core1_func = &_func;
    core1_running = true;
    multicore_launch_core1(core1_entry);
    _started = true;
    return true;
  }

 private:
  std::function<void()> _func;
  bool _started;
};

Thread::Thread() : _impl(std::make_unique<Impl>()) {}

Thread::~Thread() = default;

bool Thread::Start(std::function<void()> func) { return _impl->Start(func); }
