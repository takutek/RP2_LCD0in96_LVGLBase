#include "LvglPort/LvglPort.h"
#include "pico/time.h"
#include "DEV_Config.h"
#include "LCD_0in96.h"

void lvgl_disp_init()
{
    /*LCD Init*/
    LCD_0IN96_Init(HORIZONTAL);
    LCD_0IN96_Clear(WHITE);
    disp_driver_init();

    lv_init();

    lv_tick_set_cb(get_millis_since_startup);

    // 元 lv_disp_draw_buf_t型
    lv_display_t *display = lv_display_create(LCD_0IN96_WIDTH, LCD_0IN96_HEIGHT);

    /*LVGL will render to this 1/10 screen sized buffer for 2 bytes/pixel*/
    // 元lv_color_t型
    static uint8_t buf[LCD_0IN96_WIDTH * LCD_0IN96_HEIGHT / 10 * 2];
    lv_display_set_buffers(display, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

    /*This callback will display the rendered image*/
    lv_display_set_flush_cb(display, disp_flush_cb);
}

/*Return the elapsed milliseconds since startup.
 *It needs to be implemented by the user*/
uint32_t get_millis_since_startup()
{
    return to_us_since_boot(get_absolute_time()) / 1000ULL;
}

/*Copy the rendered image to the screen.
 *It needs to be implemented by the user*/
void disp_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_buf)
{
    // SPIの場合、エンディアンの入れ替えが必要（#define LV_COLOR_16_SWAP 1の代替）
    lv_draw_sw_rgb565_swap(px_buf, ((area->x2 + 1 - area->x1) * (area->y2 + 1 - area->y1)));

    /*Show the rendered image on the display*/
    LCD_0IN96_SetWindows(area->x1, area->y1, area->x2 + 1, area->y2 + 1);
    DEV_Digital_Write(LCD_DC_PIN, 1);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    dma_channel_configure(dma_tx,
                          &c,
                          &spi_get_hw(LCD_SPI_PORT)->dr,
                          px_buf, // read address
                          ((area->x2 + 1 - area->x1) * (area->y2 + 1 - area->y1)) * 2,
                          true);

    /*Indicate that the buffer is available.
     *If DMA were used, call in the DMA complete interrupt*/
    lv_display_flush_ready(disp);
}

void disp_driver_init()
{
    dma_channel_set_irq0_enabled(dma_tx, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);
}

void dma_handler()
{
    if (dma_channel_get_irq0_status(dma_tx))
    {
        dma_channel_acknowledge_irq0(dma_tx);
        DEV_Digital_Write(LCD_CS_PIN, 1);
        // lv_display_flush_ready(disp);
    }
}