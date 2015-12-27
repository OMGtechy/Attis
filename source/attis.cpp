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
