#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    uint64_t GetMillsSinceBoot();
    void SleepMs(uint32_t ms);

#ifdef __cplusplus
}
#endif
