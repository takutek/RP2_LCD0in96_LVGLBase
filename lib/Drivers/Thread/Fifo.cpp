#include "Drivers/Thread/Fifo.h"

#include "pico/multicore.h"

bool Fifo::can_be_pushed() const { return multicore_fifo_wready(); }

void Fifo::push(uint32_t value, bool blocking) {
  if (blocking) {
    multicore_fifo_push_blocking(value);
  } else {
    multicore_fifo_push_timeout_us(value, 0);
  }
}

bool Fifo::has_data() const { return multicore_fifo_rvalid(); }

uint32_t Fifo::pop(bool blocking) {
  if (blocking) {
    return multicore_fifo_pop_blocking();
  } else {
    uint32_t result = 0;
    multicore_fifo_pop_timeout_us(0, &result);
    return result;
  }
}