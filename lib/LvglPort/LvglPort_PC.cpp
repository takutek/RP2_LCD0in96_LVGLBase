#include "LvglPort.h"

lv_display_t* LvglPort::display = nullptr;

static lv_display_t* hal_init(int32_t w, int32_t h) {
  lv_group_set_default(lv_group_create());

  lv_display_t* disp = lv_sdl_window_create(w, h);

  lv_indev_t* mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse, lv_group_get_default());
  lv_indev_set_display(mouse, disp);
  lv_display_set_default(disp);

  LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t* cursor_obj;
  cursor_obj = lv_image_create(
      lv_screen_active()); /*Create an image object for the cursor */
  lv_image_set_src(cursor_obj, &mouse_cursor_icon); /*Set the image source*/
  lv_indev_set_cursor(mouse,
                      cursor_obj); /*Connect the image  object to the driver*/

  lv_indev_t* mousewheel = lv_sdl_mousewheel_create();
  lv_indev_set_display(mousewheel, disp);
  lv_indev_set_group(mousewheel, lv_group_get_default());

  lv_indev_t* kb = lv_sdl_keyboard_create();
  lv_indev_set_display(kb, disp);
  lv_indev_set_group(kb, lv_group_get_default());

  return disp;
}

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
  hal_init(LCD_WIDTH, LCD_HEIGHT);
}
