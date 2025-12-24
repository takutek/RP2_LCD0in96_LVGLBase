#pragma once
#include <memory>

class Gpio;

class Switch {
 public:
  enum class State { OFF = 0, ShortPress = 1, LongPress = 2 };
  Switch(int pin, bool active_low = true);
  ~Switch();
  State ReadState();
  State ReadEvent();
  void UpdateState();

 private:
  std::unique_ptr<Gpio> _gpio;
  bool _active_low;
  State _state;
  State _event;
  int _count;
  constexpr static int CONFIRM_COUNT = 5;
  constexpr static int LONG_PRESS_COUNT = 100;
};
