#pragma once
#include <memory>
#include "lvgl.h"
#include "Board/Lcd0in96/Lcd0in96.h"

class LvglPort {
public:
    LvglPort();
    static std::unique_ptr<Lcd0in96> lcd;
    static lv_display_t *display;
    static constexpr int LCD_0IN96_HEIGHT = 80;
    static constexpr int LCD_0IN96_WIDTH = 160;
private:
    static void dma_handler();
    void lvgl_disp_init();
    void disp_driver_init();
    static void my_lcd_send_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, const uint8_t *param, size_t param_size);
    static void my_lcd_send_color(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, uint8_t *param, size_t param_size);
};
