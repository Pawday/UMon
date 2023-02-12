#pragma once

#include <string>
#include <vector>
#include <optional>

template<typename T>
class ProgramArgument
{
    std::optional<char> m_singleCharAlias;
    std::string m_fullName;
    std::string m_description;
    T m_value;

public:
    ProgramArgument(char oneCharAlias, std::string fullName, std::string description);
    ProgramArgument(std::string fullName, std::string description);

    [[nodiscard]]
    std::optional<char> GetOneCharAlias() const
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

    void SetValue(const T &);

    const T &GetValue() const
    {
        return m_value;
    }
};


//TODO: Make parser class for hyphened arguments
class ArgumentTools
{
public:
    template <typename T>
    static bool ArgumentExist(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments);

    template <typename T>
    static bool HasArgDuplicates(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments);

    // Argument must exist
    // assert otherwise

    template <typename T>
    static size_t GetArgumentIndex(ProgramArgument<T> arg, std::vector<std::string> &hyphenedArguments);
};