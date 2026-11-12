#include "chess/board.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <array>


int main() {
    using namespace chess;

    Board board;

    board.put_initial_positions();

    std::cout<<"Number of figures: " << board.figure_count() << std::endl;
    
    //print the board in each rank
    for (int row = board_size-1; row >= 0; --row)
    {
        std::cout << row+1 << " ";
        for (int column = 0; column < board_size; ++column)
        {
            Figure const* figure = board.figure_at(Position{row, column});
            if (figure != nullptr)
                std::cout << figure->symbol();
            else
                std::cout << ".";
            std::cout << " ";
        }
        std::cout << row + 1 << '\n';
    }
    return 0;

}