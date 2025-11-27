#include <windows.h>

#include "Drivers/Timer/Timer.h"

unsigned long GetMillsSinceBoot() { return GetTickCount64(); }

void SleepMs(uint32_t ms) { Sleep(ms); }
