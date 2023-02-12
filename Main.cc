#include <string>
#include <iostream>

#include <array>
#include <vector>


#if HAS_WINAPI
#include <Windows.h>
#endif

#include "ProgramArgument.hh"
#include "UART.hh"


static ProgramArgument<bool> gArg_Help('h', "help", "show this message");


static ProgramArgument<UART::COMPort> gArg_UartPort('p', "port", "COM port number");
static ProgramArgument<UART::BaudRate> gArg_UartBaudRate('b', "baud-rate", "Baud rate");


static ProgramArgument<UART::ParityMode> gArg_Parity("parity",
                                                "parity mode for UART Protocol | "
                                                "possible values: none (default), odd, even, mark, space");


static ProgramArgument<UART::StopBits> gArg_StopBits('s', "stop-bits",
                                                   "amount of stop bits | "
                                                   "possible values: 1 (default), 1.5, 2");

static ProgramArgument<bool> gArg_ColorMode('c', "color-mode", "enable colors for win32 console");

static ProgramArgument<bool> gArg_ImmediateMode('i', "immediate-mode",
                                                "dont buffer input until newline, "
                                                "send input char by char to UART "
                                                "(you may not see what you're typing)");



template <typename T>
void PrintOptionUsage(ProgramArgument<T> argument)
{
    std::cout << ' ';

    std::optional<char> alias = argument.GetOneCharAlias();

    if (alias.has_value())
        std::cout << '-' << alias.value() << ' ';

    std::cout << "--" << argument.GetFullName()
            << "\t\t" << argument.GetDescription();
}

void PrintUsageAndExit()
{
    std::cout << "Usage:\n\n";
    std::cout << "Required arguments: " << '\n';
    PrintOptionUsage(gArg_UartPort);
    std::cout << '\n';

    PrintOptionUsage(gArg_UartBaudRate);
    std::cout << '\n';

    std::cout << '\n' << "Defaulted arguments:" << '\n';

    PrintOptionUsage(gArg_Parity);
    std::cout << '\n';

    PrintOptionUsage(gArg_StopBits);
    std::cout << '\n';

    std::cout << '\n';
    std::cout << "Additional options:" << '\n';

    PrintOptionUsage(gArg_ImmediateMode);
    std::cout << '\n';

    PrintOptionUsage(gArg_ColorMode);
    std::cout << '\n';

    exit(0);
}

template <typename T>
void ExitNoRequiredArgumentSpecified(ProgramArgument<T> argument)
{
    std::cout << "Option " << '\"' << argument.GetFullName() << '\"' <<  " is required" << '\n';
    std::cout << "\n\n";

    PrintUsageAndExit();
}

template <typename T>
void ExitArgumentSpecifiedMoreThanOnce(ProgramArgument<T> argument)
{
    std::cout << "Error: Option " << '\"' << argument.GetFullName() << '\"' <<  " should be specified once" << '\n';
    std::cout << "\n";

    PrintUsageAndExit();
}

template <typename T>
void ExitArgumentSpecifiedInvalid(ProgramArgument<T> argument, std::string &invalidArgumentString)
{
    std::cout << "Error: specified argument "
    << '\"' << argument.GetFullName() << '\"'
    << " with value \"" << invalidArgumentString << "\" "
    << "is not valid" << '\n';
    std::cout << "\n";

    PrintUsageAndExit();
}

template <typename T>
static void ParseArgument(std::string &hyphenedArgument, ProgramArgument<T> &argument)
{
    T gArg_Val{};

    std::stringstream gArg_Val_ParseStream(hyphenedArgument);
    gArg_Val_ParseStream >> gArg_Val;
    if (gArg_Val_ParseStream.fail() || !gArg_Val_ParseStream.eof())
        ExitArgumentSpecifiedInvalid(argument, hyphenedArgument);

    argument.SetValue(gArg_Val);
}


static void ParseToGlobalArguments(std::vector<std::string> &hyphenedArguments)
{
    gArg_Help.SetValue(ArgumentTools::ArgumentExist(gArg_Help, hyphenedArguments));

    if (gArg_Help.GetValue())
        PrintUsageAndExit();



    gArg_ColorMode.SetValue(ArgumentTools::ArgumentExist(gArg_ColorMode, hyphenedArguments));
    gArg_ImmediateMode.SetValue(ArgumentTools::ArgumentExist(gArg_ImmediateMode, hyphenedArguments));

    // Parsing UART port argument
    {
        if (!ArgumentTools::ArgumentExist(gArg_UartPort, hyphenedArguments))
            ExitNoRequiredArgumentSpecified(gArg_UartPort);

        if (ArgumentTools::HasArgDuplicates(gArg_UartPort, hyphenedArguments))
            ExitArgumentSpecifiedMoreThanOnce(gArg_UartPort);

        size_t gArg_UartPortIndex = ArgumentTools::GetArgumentIndex(gArg_UartPort, hyphenedArguments);
        ParseArgument(hyphenedArguments.at(gArg_UartPortIndex + 1), gArg_UartPort);
    }

    //Parsing baud rate
    {
        if (!ArgumentTools::ArgumentExist(gArg_UartBaudRate, hyphenedArguments))
            ExitNoRequiredArgumentSpecified(gArg_UartBaudRate);

        if (ArgumentTools::HasArgDuplicates(gArg_UartBaudRate, hyphenedArguments))
            ExitArgumentSpecifiedMoreThanOnce(gArg_UartBaudRate);

        size_t gArg_UartBaudRateIndex = ArgumentTools::GetArgumentIndex(gArg_UartBaudRate, hyphenedArguments);

        ParseArgument(hyphenedArguments.at(gArg_UartBaudRateIndex + 1), gArg_UartBaudRate);
    }




}

int main(const int argc, char *argv[argc])
{
    {
        std::vector<std::string> hyphenedArguments;

        hyphenedArguments.reserve(argc);

        for (int i = 1; i < argc; i++)
            hyphenedArguments.emplace_back(argv[i]);

        ParseToGlobalArguments(hyphenedArguments);
    }




#if HAS_WINAPI
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif



}