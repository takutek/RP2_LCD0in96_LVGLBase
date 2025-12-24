#include <windows.h>

#include "Drivers/Timer/Timer.h"

uint64_t GetMillsSinceBoot() { return GetTickCount64(); }

void SleepMs(uint32_t ms) { Sleep(ms); }
