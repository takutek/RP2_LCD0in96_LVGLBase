#pragma once

#include <cstdint>

class Fifo {
 public:
  Fifo() = default;
  ~Fifo() = default;
  Fifo(const Fifo&) = delete;
  Fifo& operator=(const Fifo&) = delete;
  Fifo(Fifo&&) = delete;
  Fifo& operator=(Fifo&&) = delete;

  bool can_be_pushed() const;
  void push(uint32_t value, bool blocking = false);
  bool has_data() const;
  uint32_t pop(bool blocking = false);
};
