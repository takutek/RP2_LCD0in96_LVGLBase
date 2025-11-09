#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned long GetMillsSinceBoot();
void SleepMs(uint32_t ms);

#ifdef __cplusplus
}
#endif
