#pragma once

#include <string>
#include <vector>

template<typename T>
class ProgramArgument
{
    char m_singleCharAlias;
    std::string m_fullName;
    std::string m_description;
    T m_value;

public:
    using Type = T;
    ProgramArgument(char oneCharAlias, std::string fullName, std::string description);

    [[nodiscard]]
    char GetOneCharAlias() const
    {
        return this->m_singleCharAlias;
    }

    [[nodiscard]]
    const std::string &GetFullName() const
    {
        return this->m_fullName;
    }

    [[nodiscard]]
    const std::string &GetDescription() const
    {
        return this->m_description;
    }

    void SetValue(T value);

    T GetValue() const
    {
        return m_value;
    }
};



//Related functions
//TODO: Make parser class for hyphened arguments

template <typename T>
bool ArgumentExist(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments);


template <typename T>
bool HasArgDuplicates(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments);

template <typename T>
size_t GetArgumentIndex(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments);