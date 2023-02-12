#pragma once

#include <cstdint>
#include <sstream>

namespace UART
{
    class COMPort
    {
    public:
        using Type = uint16_t;

    private:
        COMPort::Type m_port;

    public:

        COMPort::Type GetPort() const;
        void SetPort(COMPort::Type port);
    };

    class BaudRate
    {
    public:
        using Type = uint32_t;

    private:
        BaudRate::Type m_baudRate;

    public:

        BaudRate::Type GetBaudRate() const;
        void SetBaudRate(BaudRate::Type baudRate);
    };


    enum StopBits
    {
        ONE,
        THREEHALFS, // Q_rsqrt flashbacks
        TWO
    };

    enum ParityMode
    {
        NONE,
        ODD,
        EVEN,
        MARK,
        SPACE
    };
}


using namespace std;

stringstream& operator>>(stringstream &parseStream, UART::COMPort &output);
stringstream& operator>>(stringstream &parseStream, UART::BaudRate &output);