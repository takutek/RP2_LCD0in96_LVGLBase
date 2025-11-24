#pragma once
#include <memory>
#include <string>

class Gpio;

class Uart
{
public:
    enum class Baudrate
    {
        BAUD_9600 = 9600,
        BAUD_19200 = 19200,
        BAUD_38400 = 38400,
        BAUD_57600 = 57600,
        BAUD_115200 = 115200
    };

    enum class Port
    {
        UART0 = 0,
        UART1 = 1
    };

    Uart(Port port, int tx_pin, int rx_pin, Baudrate baudrate = Baudrate::BAUD_115200);
    ~Uart();
    void WriteString(const std::string &str);
    std::string ReadString();
    std::string QueryString(const std::string &cmd);

private:
    std::unique_ptr<Gpio> _gpio_tx;
    std::unique_ptr<Gpio> _gpio_rx;
    Port _port;
    constexpr static char terminator = '\n';
};
