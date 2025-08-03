#pragma once
#include "lvgl.h"

void lvgl_disp_init();
uint32_t get_millis_since_startup();
void disp_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_buf);
void disp_driver_init();
void dma_handler();