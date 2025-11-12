#include "Board/BoardInit/BoardInit.h"
#include "hardware/clocks.h"
#include "pico/stdlib.h"

int BoardInit::ModuleInit() {
    set_sys_clock_khz(PLL_SYS_KHZ, true);
    clock_configure(
        clk_peri,
        0,
        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,
        PLL_SYS_KHZ * 1000,
        PLL_SYS_KHZ * 1000
    );
    stdio_init_all();
    return 0;
}
