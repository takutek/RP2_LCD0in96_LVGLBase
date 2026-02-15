#include <condition_variable>
#include <mutex>
#include <queue>

#include "Fifo/Fifo.h"

static std::queue<uint32_t> g_fifo_q;
static std::mutex g_fifo_m;
static std::condition_variable g_fifo_cv;

Fifo::Fifo() = default;

bool Fifo::can_be_pushed() const { return true; }

void Fifo::push(uint32_t value, bool blocking) {
  (void)blocking;
  {
    std::lock_guard<std::mutex> lk(g_fifo_m);
    g_fifo_q.push(value);
  }
  g_fifo_cv.notify_one();
}

bool Fifo::has_data() const {
  std::lock_guard<std::mutex> lk(g_fifo_m);
  return !g_fifo_q.empty();
}

uint32_t Fifo::pop(bool blocking) {
  std::unique_lock<std::mutex> lk(g_fifo_m);
  if (blocking) {
    g_fifo_cv.wait(lk, [] { return !g_fifo_q.empty(); });
  } else {
    if (g_fifo_q.empty()) return 0;
  }
  uint32_t v = g_fifo_q.front();
  g_fifo_q.pop();
  return v;
}
