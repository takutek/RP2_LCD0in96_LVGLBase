#include "LvglPort/LvglPort.h"
#include "pico/time.h"
#include "DEV_Config.h"
#include "LCD_0in96.h"

lv_display_t *display;

/* Send command to the LCD controller */
static void my_lcd_send_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, const uint8_t *param, size_t param_size)
{
    DEV_Digital_Write(LCD_DC_PIN, 0);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    DEV_SPI_Write_nByte(LCD_SPI_PORT, (uint8_t *)cmd, cmd_size);
    DEV_Digital_Write(LCD_CS_PIN, 1);

    if (param != NULL && param_size != 0)
    {
        DEV_Digital_Write(LCD_DC_PIN, 1);
        DEV_Digital_Write(LCD_CS_PIN, 0);
        DEV_SPI_Write_nByte(LCD_SPI_PORT, (uint8_t *)param, param_size);
        DEV_Digital_Write(LCD_CS_PIN, 1);
    }
}

/* Send pixel data to the LCD controller */
static void my_lcd_send_color(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, uint8_t *param, size_t param_size)
{
    DEV_Digital_Write(LCD_DC_PIN, 0);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    DEV_SPI_Write_nByte(LCD_SPI_PORT, (uint8_t *)cmd, cmd_size);
    DEV_Digital_Write(LCD_DC_PIN, 1);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_16);
    spi_set_format(LCD_SPI_PORT, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    dma_channel_configure(dma_tx,
                          &c,
                          &spi_get_hw(LCD_SPI_PORT)->dr,
                          param,
                          param_size / 2,
                          true);
}

void lvgl_disp_init()
{
    /*LCD Init*/
    LCD_0IN96_Init(HORIZONTAL);
    disp_driver_init();

    lv_init();

    lv_tick_set_cb(get_millis_since_startup);

    display = lv_st7735_create(LCD_0IN96_HEIGHT, LCD_0IN96_WIDTH, LV_LCD_FLAG_BGR, my_lcd_send_cmd, my_lcd_send_color);
    lv_display_set_rotation(display, LV_DISPLAY_ROTATION_90);
    lv_st7735_set_gap(display, 1, 26);
    lv_st7735_set_invert(display, true);
    /*LVGL will render to this 1/10 screen sized buffer for 2 bytes/pixel*/
    static uint8_t buf[LCD_0IN96_WIDTH * LCD_0IN96_HEIGHT / 10 * 2];
    lv_display_set_buffers(display, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
}

/*Return the elapsed milliseconds since startup.
 *It needs to be implemented by the user*/
uint32_t get_millis_since_startup()
{
    return to_us_since_boot(get_absolute_time()) / 1000ULL;
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
        lv_display_flush_ready(display);
        channel_config_set_transfer_data_size(&c, DMA_SIZE_8); 
        spi_set_format(LCD_SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    }
}