
#include <iostream>
#include <string>

#include "Drivers/Uart/Uart.h"

class Gpio {
 public:
  Gpio() {};
  ~Gpio() = default;
};

Uart::Uart(Port port, int tx_pin, int rx_pin, Baudrate baudrate) {
  (void)port;
  (void)tx_pin;
  (void)rx_pin;
  (void)baudrate;
}

Uart::~Uart() = default;

void Uart::WriteString(const std::string& str) {
  std::cout << "[UART " << static_cast<int>(_port) << "] " << str << "\n";
}

std::string Uart::ReadString() {
  std::string line;
  std::cout << "[UART " << static_cast<int>(_port) << "] Waiting for input: ";
  std::getline(std::cin, line);
  return line;
}

std::string Uart::QueryString(const std::string& cmd) {
  WriteString(cmd);
  return ReadString();
}
