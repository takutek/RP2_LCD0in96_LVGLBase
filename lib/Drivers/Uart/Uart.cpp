#include "Drivers/Uart/Uart.h"

#include "Drivers/Gpio/Gpio.h"
#include "hardware/uart.h"

namespace {
uart_inst_t* port_to_uart(Uart::Port port) {
  return (port == Uart::Port::UART0) ? uart0 : uart1;
}
}  // namespace

Uart::Uart(Port port, int tx_pin, int rx_pin, Baudrate baudrate) : _port(port) {
  uart_inst_t* _uart = port_to_uart(_port);

  _gpio_tx =
      std::make_unique<Gpio>(tx_pin, Gpio::Mode::UART, Gpio::Direction::OUTPUT);
  _gpio_rx =
      std::make_unique<Gpio>(rx_pin, Gpio::Mode::UART, Gpio::Direction::INPUT);

  uart_init(_uart, static_cast<uint32_t>(baudrate));
  uart_set_format(_uart, 8, 1, UART_PARITY_NONE);
}

Uart::~Uart() { uart_deinit(port_to_uart(_port)); }

void Uart::WriteString(const std::string& str) {
  uart_puts(port_to_uart(_port), str.c_str());
}

std::string Uart::ReadString() {
  uart_inst_t* uart_instance = port_to_uart(_port);
  std::string response;
  while (uart_is_readable(uart_instance)) {
    int c = uart_getc(uart_instance);
    if (c < 0) break;
    response.push_back(static_cast<char>(c));
    if (c == static_cast<int>(terminator)) {
      return response;
    }
  }
  return response;
}

std::string Uart::QueryString(const std::string& cmd) {
  uart_inst_t* uart_instance = port_to_uart(_port);

  WriteString(cmd);

  return ReadString();
}
