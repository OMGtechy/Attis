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

#include <iostream>

int main (int argc, char* argv[])
{
    attis::StateStack state;

    for (int i = 1; i < argc; ++i)
    {
        const auto command = argv[i];
        const auto error = attis::runCommand (command, state);

        if (error != attis::Error::None)
        {
            switch (error)
            {
            case attis::Error::NotEnoughOperands: std::cout << "Not enough operands for command: " << command << std::endl; break;
            case attis::Error::UnknownOperation:  std::cout << "Unknown operation: " << command << std::endl; break;
            default:                              std::cout << "Unknown error" << std::endl;
            }

            break;
        }
    }

    if (state.size() == 0)
    {
        std::cout << "Stack empty" << std::endl;
    }
    else
    {
        std::cout << "Stack (top to bottom):" << std::endl;

        while (state.size() > 0)
        {
            std::cout << state.top() << std::endl;
            state.pop();
        }
    }
}
