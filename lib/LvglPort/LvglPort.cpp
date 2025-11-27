#include "LvglPort.h"

#include <cassert>

#include "Board/Lcd0in96/Lcd0in96.h"
#include "Drivers/Timer/Timer.h"

std::unique_ptr<Lcd0in96> LvglPort::lcd;
lv_display_t* LvglPort::display = nullptr;

extern "C" void my_lcd_send_cmd_c(lv_display_t* disp, const uint8_t* cmd,
                                  size_t cmd_size, const uint8_t* param,
                                  size_t param_size) {
  LvglPort::lcd->SendCommand(cmd, cmd_size, param, param_size);
}

extern "C" void my_lcd_send_color_c(lv_display_t* disp, const uint8_t* cmd,
                                    size_t cmd_size, uint8_t* param,
                                    size_t param_size) {
  LvglPort::lcd->SendColor(cmd, cmd_size, param, param_size);
}

extern "C" uint32_t lvgl_tick_get_wrapper() {
  return static_cast<uint32_t>(GetMillsSinceBoot());
}

void LvglPort::my_lcd_send_cmd(lv_display_t* disp, const uint8_t* cmd,
                               size_t cmd_size, const uint8_t* param,
                               size_t param_size) {
  lcd->SendCommand(cmd, cmd_size, param, param_size);
}

void LvglPort::my_lcd_send_color(lv_display_t* disp, const uint8_t* cmd,
                                 size_t cmd_size, uint8_t* param,
                                 size_t param_size) {
  lcd->SendColor(cmd, cmd_size, param, param_size);
}

void LvglPort::SetBacklightBrightness(uint8_t brightness_percent) {
  lcd->SetBacklightBrightness(brightness_percent);
}

LvglPort::LvglPort() {
  lcd = std::make_unique<Lcd0in96>();
  lv_init();

  lv_tick_set_cb(lvgl_tick_get_wrapper);
  display = lv_st7735_create(LCD_HEIGHT, LCD_WIDTH, LV_LCD_FLAG_BGR,
                             my_lcd_send_cmd_c, my_lcd_send_color_c);
  assert(display != nullptr);
  lcd->SetDmaHandler(display);
  lv_display_set_rotation(display, LCD_ROTATION);
  lv_st7735_set_gap(display, LCD_GAP_X, LCD_GAP_Y);
  lv_st7735_set_invert(display, true);
  /*LVGL will render to this 1/10 screen sized buffer for 2 bytes/pixel*/
  static uint8_t buf[LCD_WIDTH * LCD_HEIGHT / 10 * 2];
  lv_display_set_buffers(display, buf, NULL, sizeof(buf),
                         LV_DISPLAY_RENDER_MODE_PARTIAL);
}
