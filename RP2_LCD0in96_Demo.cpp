#include <cstdio>
#include <iostream>
#include <memory>
#include "pico/stdlib.h"
#include "LvglPort/LvglPort.h"
#include "Board/BoardInit/BoardInit.h"
#include "Drivers/Timer/Timer.h"
#include "Drivers/Adc/Adc.h"

int main()
{
  BoardInit::ModuleInit();
  std::cout << "RP2 LCD0in96 LVGL Temperature Sensor Demo\n";
  std::unique_ptr<LvglPort> lvglPort = std::make_unique<LvglPort>();

  // 温度センサ設定
  std::unique_ptr<Adc> adc = std::make_unique<Adc>(Adc::TEMP_SENSOR_CHANNEL);

  static lv_style_t style;
  lv_style_init(&style);

  // ウィジェット設定
  // スケール
  lv_obj_t *scale = lv_scale_create(lv_screen_active());
  lv_obj_set_size(scale, lv_pct(80), lv_pct(40));
  lv_scale_set_mode(scale, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
  lv_obj_center(scale);

  lv_scale_set_label_show(scale, true);

  lv_scale_set_total_tick_count(scale, 16);
  lv_scale_set_major_tick_every(scale, 5);

  lv_obj_set_style_length(scale, 5, LV_PART_ITEMS);
  lv_obj_set_style_length(scale, 10, LV_PART_INDICATOR);
  lv_scale_set_range(scale, 15, 30);

  // バー
  lv_obj_t *bar = lv_bar_create(lv_screen_active());
  lv_obj_set_size(bar, lv_pct(80), lv_pct(10));
  lv_obj_align_to(bar, scale, LV_ALIGN_TOP_MID, 0, -10);
  lv_bar_set_range(bar, 15, 30);

  // バーの色設定
  lv_obj_set_style_bg_color(bar, lv_color_hex(0xC0C0C0), LV_PART_MAIN);      // 背景を薄い灰色
  lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_bg_color(bar, lv_color_hex(0x1E90FF), LV_PART_INDICATOR); // インジケータを青
  lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_INDICATOR);

  // ラベル
  lv_obj_t *label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "00.00°C");
  lv_obj_add_style(label, &style, 0);
  lv_obj_align_to(label, scale, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  /*Make LVGL periodically execute its tasks*/
  while (true)
  {
    const float temp = Adc::GetTempFromAdcVoltage(adc->ReadVoltage());
    char buf[32];
    snprintf(buf, sizeof(buf), "%.2f°C", temp);
    // スケールの針を温度値に合わせる
    lv_bar_set_value(bar, (int)temp, LV_ANIM_OFF);

    // ラベルに温度値を表示
    lv_label_set_text(label, buf);
    lv_timer_handler();
    SleepMs(1000);
  }
  return 0;
}