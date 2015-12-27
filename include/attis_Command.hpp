#pragma once

#include <stack>
#include <functional>
#include <type_traits>

namespace attis
{
    enum class Error
    {
        None,
        NotEnoughOperands,
        UnknownOperation
    };

    using ValueType    = int;
    using StateStack   = std::stack<ValueType>;
    using Command      = std::function<Error (StateStack&)>;

    Error runCommand (const char*, StateStack&);
    Error runCommand (const std::string&, StateStack&);
    Error runCommand (const Command&, StateStack&);
}
