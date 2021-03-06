/*
    This file is part of Attis.

    Attis is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Attis is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Attis.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "attis_Command.hpp"

#include <algorithm>
#include <cctype>

namespace attis
{
    namespace commands
    {
        namespace
        {
            template <typename T>
            StateStack::value_type top_and_pop (T& stackLike)
            {
                const auto top = stackLike.top();
                stackLike.pop();

                return top;
            }

            template <typename T>
            Error binary_operation (StateStack& state)
            {
                if (state.size() < 2)
                    return Error::NotEnoughOperands;

                static const T operation;

                state.push (operation (top_and_pop (state), top_and_pop (state)));

                return Error::None;
            }
        }

        const Command add      = binary_operation<std::plus<ValueType>>;
        const Command subtract = binary_operation<std::minus<ValueType>>;

        const Command pop      = [] (StateStack& state)
        {
            if (state.size() < 1)
                return Error::NotEnoughOperands;

            state.pop();

            return Error::None;
        };
    }

    namespace
    {
        bool isNumber (const std::string& value)
        {
            return std::all_of (value.cbegin(), value.cend(), [] (const char character)
            {
                return std::isdigit (character);
            });
        }
    }

    Error runCommand (const char* commandName, StateStack& state)
    {
        return runCommand (std::string (commandName), state);
    }

    Error runCommand (const std::string& commandName, StateStack& state)
    {
        Command commandFunction = [] (StateStack&) { return Error::UnknownOperation; };

             if (commandName == "ADD") commandFunction = commands::add;
        else if (commandName == "SUB") commandFunction = commands::subtract;
        else if (commandName == "POP") commandFunction = commands::pop;
        else if (isNumber (commandName))
        {
            commandFunction = [commandName] (StateStack& state)
            {
                state.push (atoi (commandName.c_str()));

                return Error::None;
            };
        }

        return commandFunction (state);
    }
}
