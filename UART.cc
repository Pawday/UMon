#include "UART.hh"

using namespace UART;

COMPort::Type UART::COMPort::GetPort() const
{
    return this->m_port;
}

void COMPort::SetPort(COMPort::Type mPort)
{
    this->m_port = mPort;
}


BaudRate::Type BaudRate::GetBaudRate() const
{
    return this->m_baudRate;
}

void BaudRate::SetBaudRate(BaudRate::Type baudRate)
{
    this->m_baudRate = baudRate;
}


using namespace std;

//Defining parsers for out wrappers

stringstream& operator>>(stringstream &parseStream, UART::COMPort &output)
{
    UART::COMPort::Type portNum;

    parseStream >> portNum;

    output.SetPort(portNum);

    return parseStream;
}

stringstream &operator>>(stringstream &parseStream, UART::BaudRate &output)
{
    UART::BaudRate::Type baudRateNum;

    parseStream >> baudRateNum;

    output.SetBaudRate(baudRateNum);

    return parseStream;
}

/*

//if above code will grow, make it templated via concepts bellow


template <typename T>
constexpr bool UARTSingleFieldedT = false;

template <>
constexpr bool UARTSingleFieldedT<UART::BaudRate> = true;

template <>
constexpr bool UARTSingleFieldedT<UART::COMPort> = true;

template <typename T>
concept UARTSingleFielded = UARTSingleFieldedT<T>;

template <UARTSingleFielded T>
stringstream& operator>>(stringstream &parseStream, T &output)
{
    typename T::ArgType internalValue;

    parseStream >> internalValue;

    output.SetValue(internalValue);

    return parseStream;
}
*/