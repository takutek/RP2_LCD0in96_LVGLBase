#include <cassert>

#include "Drivers/Timer/Timer.h"
#include "LvglPort.h"
#include "hal/hal.h"

lv_display_t* LvglPort::display = nullptr;

void LvglPort::my_lcd_send_cmd(lv_display_t* disp, const uint8_t* cmd,
                               size_t cmd_size, const uint8_t* param,
                               size_t param_size) {
  (void)disp;
  (void)cmd;
  (void)cmd_size;
  (void)param;
  (void)param_size;
}

void LvglPort::my_lcd_send_color(lv_display_t* disp, const uint8_t* cmd,
                                 size_t cmd_size, uint8_t* param,
                                 size_t param_size) {
  (void)disp;
  (void)cmd;
  (void)cmd_size;
  (void)param;
  (void)param_size;
}

void LvglPort::SetBacklightBrightness(uint8_t brightness_percent) {
  (void)brightness_percent;
}

LvglPort::LvglPort() {
  lv_init();
  sdl_hal_init(LCD_WIDTH, LCD_HEIGHT);
}
