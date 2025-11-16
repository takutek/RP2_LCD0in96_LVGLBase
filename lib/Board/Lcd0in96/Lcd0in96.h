#pragma once
#include <memory>
#include "lvgl.h"

// Forward declarations
class Gpio;
class Pwm;
class Spi;
class Dma;

class Lcd0in96 {
public:
    Lcd0in96();
    ~Lcd0in96();
    void SetDmaHandler(lv_display_t *display);
    void SendCommand(const uint8_t *cmd, size_t cmd_size, const uint8_t *param, size_t param_size);
    void SendColor(const uint8_t *cmd, size_t cmd_size, uint8_t *param, size_t param_size);
    void SetBacklightBrightness(uint8_t brightness_percent);
    static void dma_handler();

private:
    static lv_display_t* _display;
    static std::unique_ptr<Dma> _dma;
    static std::unique_ptr<Gpio> _cs;
    std::unique_ptr<Gpio> _dc;
    std::unique_ptr<Gpio> _rst;
    std::unique_ptr<Pwm> _bl;
    static std::unique_ptr<Spi> _spi;

    constexpr static int LCD_DC_PIN = 8;
    constexpr static int LCD_CS_PIN = 9;
    constexpr static int LCD_CLK_PIN = 10;
    constexpr static int LCD_MOSI_PIN = 11;
    constexpr static int LCD_RST_PIN = 12;
    constexpr static int LCD_BL_PIN = 25;
    constexpr static int LCD_SPI_PORT = 1;
    constexpr static int LCD_SPI_BAUDRATE = 150 * 1000 * 1000;
    constexpr static int LCD_RST_PULSE_MS = 1;
    constexpr static int LCD_RST_WAIT_MS = 120;

    void SendData(const uint8_t *data, size_t size);
    void InitLcdGpio();
    void InitLcdPwm();
    void InitLcdSpi();
    void InitLcdDma();
    void LcdReset();
};
