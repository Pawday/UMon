#include <string>
#include <array>
#include <vector>
#include <cinttypes>
#include <iostream>

#if HAS_WINAPI
#include <Windows.h>
#endif

#include "ProgramArgument.hh"

static ProgramArgument<uint16_t> gArg_UartPort('p', "port", "COM port number");
static ProgramArgument<uint32_t> gArg_BaudRate('b', "baud-rate", "Baud rate");

static ProgramArgument<bool> gArg_Help('h', "help", "show this message");
static ProgramArgument<bool> gArg_ColorMode('c', "color-mode", "enable colors for win32 console");

static ProgramArgument<bool> gArg_ImmediateMode('i', "immediate-mode",
                                                "dont buffer input until newline, "
                                                "send input char by char to UART "
                                                "(you may not see what you're typing)");


template <typename T>
void PrintOptionUsage(ProgramArgument<T> argument)
{
    std::cout
            << ' '
            << '-' << argument.GetOneCharAlias()
            << ' '
            << "--" << argument.GetFullName()
            << ' ' << argument.GetDescription();
}

void PrintUsageAndExit()
{
    std::cout << "Usage:\n";
    std::cout << "Required arguments: " << '\n';
    PrintOptionUsage(gArg_UartPort);
    std::cout << '\n';

    PrintOptionUsage(gArg_BaudRate);
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
    std::cout << "Option << " << '\"' << argument.GetFullName() << '\"' <<  " is required" << '\n';
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


static void ParseToGlobalArguments(std::vector<std::string> &hyphenedArguments)
{
    gArg_Help.SetValue(ArgumentExist(gArg_Help, hyphenedArguments));

    if (gArg_Help.GetValue())
        PrintUsageAndExit();


    gArg_ColorMode.SetValue(ArgumentExist(gArg_ColorMode, hyphenedArguments));
    gArg_ImmediateMode.SetValue(ArgumentExist(gArg_ImmediateMode, hyphenedArguments));

    if (!ArgumentExist(gArg_UartPort, hyphenedArguments))
        ExitNoRequiredArgumentSpecified(gArg_UartPort);

    if (HasArgDuplicates(gArg_UartPort, hyphenedArguments))
        ExitArgumentSpecifiedMoreThanOnce(gArg_UartPort);

    size_t gArg_UartPortIndex = GetArgumentIndex(gArg_UartPort, hyphenedArguments);
    size_t gArg_Val_UartPortIndex = gArg_UartPortIndex + 1;

    gArg_UartPort.SetValue(std::stoi(hyphenedArguments.at(gArg_Val_UartPortIndex)));


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