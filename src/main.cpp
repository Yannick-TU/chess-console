// #include "chess/board.hpp"

// #include <iostream>
// #include <memory>
// #include <vector>
// #include <array>


// int main() {
//     using namespace chess;

//     Board board;

//     board.put_initial_positions();

//     std::cout<<"Number of figures: " << board.figure_count() << std::endl;
    
//     //print the board in each rank
//     for (int row = board_size-1; row >= 0; --row)
//     {
//         std::cout << row+1 << " ";
//         for (int column = 0; column < board_size; ++column)
//         {
//             Figure const* figure = board.figure_at(Position{row, column});
//             if (figure != nullptr)
//                 std::cout << figure->symbol();
//             else
//                 std::cout << ".";
//             std::cout << " ";
//         }
//         std::cout << row + 1 << '\n';
//     }
//     return 0;

// }


#include <iostream>

#include "chess/board.hpp"
#include "chess/king.hpp"
#include "chess/pawn.hpp"
#include <memory>
int main()
{
    chess::Board board;

    chess::King king{chess::Color::White};

    // King stands on e4
    chess::Position current_pos{3, 4};
    board.place_figure(chess::Position{4,4}, std::make_unique<chess::Pawn>(chess::Color::White));
    auto moves = king.legal_moves(current_pos, board);

    std::cout << "Possible King moves from e4:\n";

    for (auto const& move : moves)
    {
        auto notation = move.toAlgebraic();

        if (notation)
            std::cout << *notation << '\n';
    }

    std::cout << "\nNumber of possible moves: "
              << moves.size() << '\n';

    return 0;
}
