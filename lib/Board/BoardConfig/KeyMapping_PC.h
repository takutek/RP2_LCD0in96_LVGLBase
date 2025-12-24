#pragma once

#include <SDL.h>

#include <unordered_map>

#include "Board/BoardConfig/BoardConfig.h"

namespace KeyMapping {
inline const std::unordered_map<int, SDL_Scancode> PIN_TO_KEY = {
    {PinConfig::SWITCH_PIN, SDL_SCANCODE_2},
};
}  // namespace KeyMapping