#include <ranges>
#include <cassert>

#include "ProgramArgument.hh"

template<typename T>
ProgramArgument<T>::ProgramArgument(char oneCharAlias, std::string fullName, std::string description):
m_singleCharAlias(oneCharAlias),
m_fullName(std::move(fullName)),
m_description(std::move(description)) {}

template ProgramArgument<bool>::ProgramArgument(char oneCharAlias, std::string fullName, std::string description);
template ProgramArgument<uint16_t>::ProgramArgument(char oneCharAlias, std::string fullName, std::string description);
template ProgramArgument<uint32_t>::ProgramArgument(char oneCharAlias, std::string fullName, std::string description);


template<typename T>
void ProgramArgument<T>::SetValue(T value)
{
    ProgramArgument::m_value = value;
}

template void ProgramArgument<bool>::SetValue(bool value);
template void ProgramArgument<uint16_t>::SetValue(uint16_t value);
template void ProgramArgument<uint32_t>::SetValue(uint32_t value);


//Helper functions

template <typename T>
bool HasArgDuplicates(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments)
{
    if (!ArgumentExist(arg, hyphenedArguments)) return false;

    std::string argShortAliasHyphened = std::move(std::string("-") + arg.GetOneCharAlias());
    std::string argFullNameHyphened = std::move(std::string("--") + arg.GetFullName());

    auto argShortAliasAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argShortAliasHyphened);
    auto argFullNameAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argFullNameHyphened);

    if (argShortAliasAmount > 1) return true;
    if (argFullNameAmount > 1) return true;

    if (argShortAliasAmount == 1 && argFullNameAmount == 1) return true;

    return false;
}

template bool HasArgDuplicates<bool>(ProgramArgument<bool> arg, std::vector<std::string> &hyphenedArguments);
template bool HasArgDuplicates<uint16_t>(ProgramArgument<uint16_t> arg, std::vector<std::string> &hyphenedArguments);
template bool HasArgDuplicates<uint32_t>(ProgramArgument<uint32_t> arg, std::vector<std::string> &hyphenedArguments);



template <typename T>
bool ArgumentExist(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments)
{
    std::string argShortAliasHyphened = std::move(std::string("-") + arg.GetOneCharAlias());
    std::string argFullNameHyphened = std::move(std::string("--") + arg.GetFullName());

    auto argShortAliasAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argShortAliasHyphened);
    auto argFullNameAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argFullNameHyphened);

    if (argShortAliasAmount == 0 && argFullNameAmount == 0)
        return false;

    return true;
}

template bool ArgumentExist<bool>(ProgramArgument<bool> arg, std::vector<std::string> &hyphenedArguments);
template bool ArgumentExist<uint16_t>(ProgramArgument<uint16_t> arg, std::vector<std::string> &hyphenedArguments);
template bool ArgumentExist<uint32_t>(ProgramArgument<uint32_t> arg, std::vector<std::string> &hyphenedArguments);


template <typename T>
size_t GetArgumentIndex(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments)
{
    using namespace std;
    std::string argShortAliasHyphened = std::move(std::string("-") + arg.GetOneCharAlias());
    std::string argFullNameHyphened = std::move(std::string("--") + arg.GetFullName());

    auto argShortAliasAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argShortAliasHyphened);
    auto argFullNameAmount = std::count(hyphenedArguments.begin(), hyphenedArguments.end(), argFullNameHyphened);

    auto shortVariantFoundIT = std::find(hyphenedArguments.begin(), hyphenedArguments.end(), argShortAliasHyphened);

    if (shortVariantFoundIT != hyphenedArguments.end())
        return shortVariantFoundIT - hyphenedArguments.begin();

    auto longVariantFoundIT = std::find(hyphenedArguments.begin(), hyphenedArguments.end(), argFullNameHyphened);

    assert(longVariantFoundIT != hyphenedArguments.end());

    return longVariantFoundIT - hyphenedArguments.begin();
}

template size_t GetArgumentIndex<bool> (ProgramArgument<bool> arg, std::vector<std::string> &hyphenedArguments);
template size_t GetArgumentIndex<uint16_t> (ProgramArgument<uint16_t> arg, std::vector<std::string> &hyphenedArguments);
template size_t GetArgumentIndex<uint32_t> (ProgramArgument<uint32_t> arg, std::vector<std::string> &hyphenedArguments);