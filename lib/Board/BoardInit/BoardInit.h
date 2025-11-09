#pragma once

class BoardInit {
public:
    static int ModuleInit();
private:
    constexpr static int PLL_SYS_KHZ = 150 * 1000;
};
