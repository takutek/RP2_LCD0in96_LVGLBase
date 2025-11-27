#pragma once
#include <memory>

#include "Drivers/Gpio/Gpio.h"

class Spi {
 public:
  Spi(int port, int clk_pin, int mosi_pin, int miso_pin, uint32_t baudrate);
  int GetDreq(bool is_tx) const;
  void SetTransferSize(int size);
  uint32_t GetTxRegisterAddr() const;
  void WriteNByte(const uint8_t* data, size_t size) const;

 private:
  int _port;
  int _size = 8;
  std::unique_ptr<Gpio> _clk;
  std::unique_ptr<Gpio> _mosi;
  std::unique_ptr<Gpio> _miso;
};
