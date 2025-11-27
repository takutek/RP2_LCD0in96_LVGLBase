#include "Drivers/Timer/Timer.h"

#include "pico/time.h"

uint64_t GetMillsSinceBoot() { return to_ms_since_boot(get_absolute_time()); }
void SleepMs(uint32_t ms) { sleep_ms(ms); }
