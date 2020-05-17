#include "jezzball/Board.hpp"

#include <iostream>
#include <memory>


int main(int argc, char* args[])
{
    std::unique_ptr<jezzball::Board> board = std::make_unique<jezzball::Board>();

    if (!board->init())
    {
        std::cout << "Could not initialize Jezzball" << std::endl;
    }
    else
    {
        board->gameLoop();
    }

    board->close();

    return 0;
}
