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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

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
