#include "Drivers/Timer/Timer.h"

#include "pico/time.h"

uint64_t GetMillsSinceBoot() { return to_ms_since_boot(get_absolute_time()); }
void SleepMs(uint32_t ms) { sleep_ms(ms); }

class Timer::Impl {
 public:
  repeating_timer_t timer_{};
  std::unique_ptr<Timer::Callback> callback_;

  static bool CallbackAdapter(repeating_timer_t* rt) {
    auto* impl = static_cast<Impl*>(rt->user_data);
    return impl && impl->callback_ ? (*impl->callback_)() : false;
  }
};

Timer::Timer() : impl_(std::make_unique<Impl>()) {}

Timer::~Timer() { Cancel(); }

bool Timer::RegisterCallback(Callback&& cb, uint32_t interval_ms) {
  Cancel();
  impl_->callback_ = std::make_unique<Callback>(std::move(cb));
  return add_repeating_timer_ms(interval_ms, Impl::CallbackAdapter, impl_.get(),
                                &impl_->timer_);
}

bool Timer::Cancel() {
  impl_->callback_.reset();
  return cancel_repeating_timer(&impl_->timer_);
}
