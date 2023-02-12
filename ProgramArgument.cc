#include <ranges>
#include <cassert>

#include "ProgramArgument.hh"
#include "UART.hh"

template<typename T>
ProgramArgument<T>::ProgramArgument(char oneCharAlias, std::string fullName, std::string description):
m_singleCharAlias(oneCharAlias),
m_fullName(std::move(fullName)),
m_description(std::move(description)) {}

template ProgramArgument<bool>::ProgramArgument(char oneCharAlias, std::string fullName, std::string description);
template ProgramArgument<UART::BaudRate>::ProgramArgument(char oneCharAlias, std::string fullName, std::string description);
template ProgramArgument<UART::COMPort>::ProgramArgument(char oneCharAlias, std::string fullName, std::string description);
template ProgramArgument<UART::ParityMode>::ProgramArgument(char oneCharAlias, std::string fullName, std::string description);
template ProgramArgument<UART::StopBits>::ProgramArgument(char oneCharAlias, std::string fullName, std::string description);

template<typename T>
ProgramArgument<T>::ProgramArgument(std::string fullName, std::string description):
        m_fullName(std::move(fullName)),
        m_description(std::move(description)) {}

template ProgramArgument<bool>::ProgramArgument(std::string fullName, std::string description);
template ProgramArgument<UART::COMPort>::ProgramArgument(std::string fullName, std::string description);
template ProgramArgument<UART::BaudRate>::ProgramArgument(std::string fullName, std::string description);
template ProgramArgument<UART::ParityMode>::ProgramArgument(std::string fullName, std::string description);
template ProgramArgument<UART::StopBits>::ProgramArgument(std::string fullName, std::string description);


template<typename T>
void ProgramArgument<T>::SetValue(const T &value)
{
    ProgramArgument::m_value = value;
}

template void ProgramArgument<bool>::SetValue(const bool &value);
template void ProgramArgument<UART::BaudRate>::SetValue(const UART::BaudRate &baudRate);
template void ProgramArgument<UART::COMPort>::SetValue(const UART::COMPort &comPort);
template void ProgramArgument<UART::ParityMode>::SetValue(const UART::ParityMode &parityMode);
template void ProgramArgument<UART::StopBits>::SetValue(const UART::StopBits &stopBits);


//Argument Tools

template <typename T>
bool ArgumentTools::HasArgDuplicates(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments)
{
    if (!ArgumentTools::ArgumentExist(arg, hyphenedArguments)) return false;

    const std::optional<char> &shortAlias = arg.GetOneCharAlias();

    size_t argShortAliasAmount;

    if (!shortAlias.has_value())
        argShortAliasAmount = 0;
    else
    {
        std::string argShortAliasHyphened = std::move(std::string("-") + shortAlias.value());
        argShortAliasAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argShortAliasHyphened);
        if (argShortAliasAmount > 1) return true;
    }


    std::string argFullNameHyphened = std::move(std::string("--") + arg.GetFullName());

    auto argFullNameAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argFullNameHyphened);
    if (argFullNameAmount > 1) return true;

    if (argShortAliasAmount == 1 && argFullNameAmount == 1) return true;

    return false;
}

template bool ArgumentTools::HasArgDuplicates<bool>(ProgramArgument<bool> arg, std::vector<std::string> &hyphenedArguments);
template bool ArgumentTools::HasArgDuplicates<UART::BaudRate>(ProgramArgument<UART::BaudRate> arg, std::vector<std::string> &hyphenedArguments);
template bool ArgumentTools::HasArgDuplicates<UART::COMPort>(ProgramArgument<UART::COMPort> arg, std::vector<std::string> &hyphenedArguments);
template bool ArgumentTools::HasArgDuplicates<UART::ParityMode>(ProgramArgument<UART::ParityMode> arg, std::vector<std::string> &hyphenedArguments);
template bool ArgumentTools::HasArgDuplicates<UART::StopBits>(ProgramArgument<UART::StopBits> arg, std::vector<std::string> &hyphenedArguments);



template <typename T>
bool ArgumentTools::ArgumentExist(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments)
{
    const std::optional<char> &shortAlias = arg.GetOneCharAlias();

    size_t argShortAliasAmount;

    if (!shortAlias.has_value())
        argShortAliasAmount = 0;
    else
    {
        std::string argShortAliasHyphened = std::move(std::string("-") + shortAlias.value());
        argShortAliasAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argShortAliasHyphened);
        if (argShortAliasAmount > 1) return true;
    }

    std::string argFullNameHyphened = std::move(std::string("--") + arg.GetFullName());

    auto argFullNameAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argFullNameHyphened);

    if (argShortAliasAmount == 0 && argFullNameAmount == 0)
        return false;

    return true;
}

template bool ArgumentTools::ArgumentExist<bool>(ProgramArgument<bool> arg, std::vector<std::string> &hyphenedArguments);
template bool ArgumentTools::ArgumentExist<UART::BaudRate>(ProgramArgument<UART::BaudRate> arg, std::vector<std::string> &hyphenedArguments);
template bool ArgumentTools::ArgumentExist<UART::COMPort>(ProgramArgument<UART::COMPort> arg, std::vector<std::string> &hyphenedArguments);
template bool ArgumentTools::ArgumentExist<UART::ParityMode>(ProgramArgument<UART::ParityMode> arg, std::vector<std::string> &hyphenedArguments);
template bool ArgumentTools::ArgumentExist<UART::StopBits>(ProgramArgument<UART::StopBits> arg, std::vector<std::string> &hyphenedArguments);


template <typename T>
size_t ArgumentTools::GetArgumentIndex(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments)
{
    const std::optional<char> &shortAlias = arg.GetOneCharAlias();

    size_t argShortAliasAmount;

    std::string argShortAliasHyphened;

    if (!shortAlias.has_value())
        argShortAliasAmount = 0;
    else
    {
        argShortAliasHyphened = std::move(std::string("-") + shortAlias.value());
        argShortAliasAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argShortAliasHyphened);
        if (argShortAliasAmount > 1) return true;
    }

    std::string argFullNameHyphened = std::move(std::string("--") + arg.GetFullName());

    auto argFullNameAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argFullNameHyphened);

    if (shortAlias.has_value())
    {
        auto shortVariantFoundIT = std::find(hyphenedArguments.begin(), hyphenedArguments.end(), argShortAliasHyphened);

        if (shortVariantFoundIT != hyphenedArguments.end())
            return shortVariantFoundIT - hyphenedArguments.begin();
    }


    auto longVariantFoundIT = std::find(hyphenedArguments.begin(), hyphenedArguments.end(), argFullNameHyphened);

    // Aka there is no argument
    assert(longVariantFoundIT != hyphenedArguments.end());

    return longVariantFoundIT - hyphenedArguments.begin();
}

template size_t ArgumentTools::GetArgumentIndex<bool> (ProgramArgument<bool> arg, std::vector<std::string> &hyphenedArguments);
template size_t ArgumentTools::GetArgumentIndex<UART::BaudRate> (ProgramArgument<UART::BaudRate> arg, std::vector<std::string> &hyphenedArguments);
template size_t ArgumentTools::GetArgumentIndex<UART::COMPort> (ProgramArgument<UART::COMPort> arg, std::vector<std::string> &hyphenedArguments);
template size_t ArgumentTools::GetArgumentIndex<UART::ParityMode> (ProgramArgument<UART::ParityMode> arg, std::vector<std::string> &hyphenedArguments);
template size_t ArgumentTools::GetArgumentIndex<UART::ParityMode> (ProgramArgument<UART::ParityMode> arg, std::vector<std::string> &hyphenedArguments);