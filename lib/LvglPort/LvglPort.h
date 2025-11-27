#pragma once
#include <memory>

#include "lvgl.h"

class Lcd0in96;

class LvglPort {
 public:
  LvglPort();
  void SetBacklightBrightness(uint8_t brightness_percent);
  static std::unique_ptr<Lcd0in96> lcd;
  static lv_display_t* display;

 private:
  static constexpr int LCD_HEIGHT = 80;
  static constexpr int LCD_WIDTH = 160;
  static constexpr int LCD_GAP_X = 1;
  static constexpr int LCD_GAP_Y = 27;
  static constexpr lv_display_rotation_t LCD_ROTATION = LV_DISPLAY_ROTATION_90;
  static void dma_handler();
  void lvgl_disp_init();
  void disp_driver_init();
  static void my_lcd_send_cmd(lv_display_t* disp, const uint8_t* cmd,
                              size_t cmd_size, const uint8_t* param,
                              size_t param_size);
  static void my_lcd_send_color(lv_display_t* disp, const uint8_t* cmd,
                                size_t cmd_size, uint8_t* param,
                                size_t param_size);
};
