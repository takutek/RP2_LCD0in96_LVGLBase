#include "Drivers/Spi/Spi.h"
#include "hardware/spi.h"

Spi::Spi(int port, int clk_pin, int mosi_pin, int miso_pin, int cs_pin, uint32_t baudrate) {
    _port = port;
    spi_inst_t* spi_port = (port == 0) ? spi0 : spi1;
    spi_init(spi_port, baudrate);

    _clk = std::make_unique<Gpio>(clk_pin);
    _clk->SetMode(Gpio::Mode::SPI);

    _mosi = std::make_unique<Gpio>(mosi_pin);
    _mosi->SetMode(Gpio::Mode::SPI);

    (void)miso_pin;

    SetTransferSize(_size);
}

int Spi::GetDreq(bool is_tx) const {
    spi_inst_t* spi_port = (_port == 0) ? spi0 : spi1;
    return spi_get_dreq(spi_port, is_tx);
}

void Spi::SetTransferSize(int size) {
    _size = size;
    spi_inst_t* spi_port = (_port == 0) ? spi0 : spi1;
    spi_set_format(spi_port, _size, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
}

void Spi::isMsbFirst(bool MsbFirst) const {
    spi_inst_t* spi_port = (_port == 0) ? spi0 : spi1;
    spi_order_t order = MsbFirst ? SPI_MSB_FIRST : SPI_LSB_FIRST;
    spi_set_format(spi_port, _size, SPI_CPOL_0, SPI_CPHA_0, order);
}

uint32_t Spi::GetTxRegisterAddr() const {
    spi_inst_t* spi_port = (_port == 0) ? spi0 : spi1;
    return reinterpret_cast<uint32_t>(&spi_get_hw(spi_port)->dr);
}

void Spi::WriteNByte(const uint8_t* data, size_t size) const {
    spi_inst_t* spi_port = (_port == 0) ? spi0 : spi1;
    spi_write_blocking(spi_port, data, size);
}
