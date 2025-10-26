#pragma once
#include "lvgl.h"

void lvgl_disp_init();
uint32_t get_millis_since_startup();
void disp_driver_init();
void dma_handler();