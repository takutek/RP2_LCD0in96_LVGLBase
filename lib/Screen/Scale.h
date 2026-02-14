#pragma once

#include "Screen.h"
#include "lvgl.h"

class Scale : public Screen {
 public:
  Scale() = default;
  ~Scale() override = default;
  Scale(const Scale&) = delete;
  Scale& operator=(const Scale&) = delete;

  void Create() override;
  void Destroy() override;
  void Update(void* data) override;

 private:
  lv_obj_t* _scale = nullptr;
  lv_obj_t* _bar = nullptr;
  lv_obj_t* _label = nullptr;
};