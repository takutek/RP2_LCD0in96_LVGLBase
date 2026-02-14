#include "Scale.h"

#include <cstdio>
#include <cstring>

#include "lvgl.h"

void Scale::Create() {
  _scale = lv_scale_create(lv_screen_active());
  lv_obj_set_size(_scale, lv_pct(80), lv_pct(40));
  lv_scale_set_mode(_scale, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
  lv_obj_center(_scale);

  lv_scale_set_label_show(_scale, true);
  lv_scale_set_total_tick_count(_scale, 16);
  lv_scale_set_major_tick_every(_scale, 5);
  lv_obj_set_style_length(_scale, 5, LV_PART_ITEMS);
  lv_obj_set_style_length(_scale, 10, LV_PART_INDICATOR);
  lv_scale_set_range(_scale, 15, 30);

  _bar = lv_bar_create(lv_screen_active());
  lv_obj_set_size(_bar, lv_pct(80), lv_pct(10));
  lv_obj_align_to(_bar, _scale, LV_ALIGN_TOP_MID, 0, -10);
  lv_bar_set_range(_bar, 15, 30);

  lv_obj_set_style_bg_color(_bar, lv_color_hex(0xC0C0C0), LV_PART_MAIN);
  lv_obj_set_style_bg_opa(_bar, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_bg_color(_bar, lv_color_hex(0x1E90FF), LV_PART_INDICATOR);
  lv_obj_set_style_bg_opa(_bar, LV_OPA_COVER, LV_PART_INDICATOR);

  _label = lv_label_create(lv_screen_active());
  lv_label_set_text(_label, "00.00°C");
  lv_obj_align_to(_label, _scale, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
}

void Scale::Destroy() {
  if (_label != nullptr) {
    lv_obj_delete(_label);
    _label = nullptr;
  }
  if (_bar != nullptr) {
    lv_obj_delete(_bar);
    _bar = nullptr;
  }
  if (_scale != nullptr) {
    lv_obj_delete(_scale);
    _scale = nullptr;
  }
}

void Scale::Update(void* data) {
  if (data == nullptr || _bar == nullptr || _label == nullptr) {
    return;
  }

  float temp = 0.0f;
  std::memcpy(&temp, data, sizeof(float));

  char buf[32];
  snprintf(buf, sizeof(buf), "%.2f°C", temp);
  lv_bar_set_value(_bar, static_cast<int>(temp), LV_ANIM_OFF);
  lv_label_set_text(_label, buf);
  lv_timer_handler();
}