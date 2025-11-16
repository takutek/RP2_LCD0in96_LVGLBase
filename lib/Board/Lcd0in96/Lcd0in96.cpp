#include "Board/Lcd0in96/Lcd0in96.h"
#include "Drivers/Gpio/Gpio.h"
#include "Drivers/Pwm/Pwm.h"
#include "Drivers/Spi/Spi.h"
#include "Drivers/Dma/Dma.h"
#include "Drivers/Timer/Timer.h"

lv_display_t* Lcd0in96::_display = nullptr;
std::unique_ptr<Gpio> Lcd0in96::_cs = nullptr;
std::unique_ptr<Spi> Lcd0in96::_spi = nullptr;
std::unique_ptr<Dma> Lcd0in96::_dma = nullptr;

extern "C" void dma_handler_c() {
    Lcd0in96::dma_handler();
}

void Lcd0in96::SendData(const uint8_t *data, size_t size) {
    _cs->Write(false);
    _spi->WriteNByte(data, size);
    _cs->Write(true);
}

void Lcd0in96::SendCommand(const uint8_t *cmd, size_t cmd_size, const uint8_t *param, size_t param_size) {
    _dc -> Write(false);
    SendData(cmd, cmd_size);

    if (param != nullptr && param_size != 0) {
        _dc -> Write(true);
        SendData(param, param_size);
    }
}

void Lcd0in96::SendColor(const uint8_t *cmd, size_t cmd_size, uint8_t *param, size_t param_size) {
    _dc -> Write(false);
    SendData(cmd, cmd_size);

    _cs->Write(false);
    _dc -> Write(true);
    _dma->SetTransferSize(Dma::TransferSize::SIZE_16bit);
    _spi->SetTransferSize(16);
    _dma->ConfigureAndStart(reinterpret_cast<uint32_t>(param),
                           _spi->GetTxRegisterAddr(),
                           param_size / 2);
}

void Lcd0in96::InitLcdGpio() {
    _rst = std::make_unique<Gpio>(LCD_RST_PIN, Gpio::OUTPUT);
    _rst->Write(true);
    _cs =  std::make_unique<Gpio>(LCD_CS_PIN, Gpio::OUTPUT);
    _cs->Write(true);
    _dc = std::make_unique<Gpio>(LCD_DC_PIN, Gpio::OUTPUT);
    _dc->Write(true);
}

void Lcd0in96::InitLcdPwm() {
    _bl = std::make_unique<Pwm>(LCD_BL_PIN);
    _bl->SetClockDivider(50);
    _bl->SetWrap(100);
    _bl->SetDuty(70);
    _bl->Enable();
}

void Lcd0in96::InitLcdSpi() {
    _spi = std::make_unique<Spi>(LCD_SPI_PORT, LCD_CLK_PIN, LCD_MOSI_PIN, 0, LCD_SPI_BAUDRATE);
}

void Lcd0in96::InitLcdDma() {
    _dma = std::make_unique<Dma>(Dma::TransferSize::SIZE_8bit);
    _dma->SetDreq(_spi->GetDreq(true));
}

void Lcd0in96::LcdReset() {
    _rst->Write(false);
    SleepMs(LCD_RST_PULSE_MS);
    _rst->Write(true);
    SleepMs(LCD_RST_WAIT_MS);
}

void Lcd0in96::SetBacklightBrightness(uint8_t brightness_percent) {
    if (brightness_percent > 100) {
        brightness_percent = 100;
    }
    if (brightness_percent == 0) {
        brightness_percent = 1;
    }
    _bl->SetDuty(brightness_percent);
}

Lcd0in96::Lcd0in96() {
    InitLcdGpio();
    InitLcdPwm();
    InitLcdSpi();
    InitLcdDma();
    LcdReset();
}

Lcd0in96::~Lcd0in96() = default;

void Lcd0in96::dma_handler() {
    if (_dma->isDone()) {
        _dma->AckIrq();
        _cs->Write(true);
        _dma->SetTransferSize(Dma::TransferSize::SIZE_8bit);
        _spi->SetTransferSize(8);
        lv_display_flush_ready(_display);
    }
}

void Lcd0in96::SetDmaHandler(lv_display_t *display) {
    _display = display;
    _dma->SetIrq(dma_handler_c);
}
