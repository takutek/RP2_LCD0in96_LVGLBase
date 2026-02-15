#pragma once
#include <memory>

class Gpio;

class Switch {
 public:
  enum class State { OFF = 0, ShortPress = 1, LongPress = 2 };
  Switch(int pin, bool active_low = true);
  ~Switch();

  Switch(const Switch&) = delete;
  Switch& operator=(const Switch&) = delete;
  Switch(Switch&&) = delete;
  Switch& operator=(Switch&&) = delete;

  State ReadState();
  State ReadEvent();
  void UpdateState();

 private:
  std::unique_ptr<Gpio> _gpio;
  int _count;
  State _state;
  State _event;
  bool _active_low;
  constexpr static int CONFIRM_COUNT = 5;
  constexpr static int LONG_PRESS_COUNT = 100;
};
