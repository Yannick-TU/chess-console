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
#include <memory>

#include "chess/board.hpp"
#include "chess/bishop.hpp"
#include "chess/queen.hpp"
#include "chess/pawn.hpp"

int main()
{
    chess::Position position{3, 4}; // e4

    // Test 1: Bishop on empty board
    chess::Board empty_board;

    chess::Bishop bishop{chess::Color::White};
    chess::Queen queen{chess::Color::White};

    auto bishop_moves = bishop.legal_moves(position, empty_board);
    auto queen_moves = queen.legal_moves(position, empty_board);

    std::cout << "Bishop moves on empty board: "
              << bishop_moves.size() << '\n';

    std::cout << "Queen moves on empty board: "
              << queen_moves.size() << '\n';


    // Test 2: Add obstacles
    chess::Board blocked_board;

    blocked_board.place_figure(
        chess::Position{5, 6},
        std::make_unique<chess::Pawn>(chess::Color::White)
    );

    blocked_board.place_figure(
        chess::Position{5, 2},
        std::make_unique<chess::Pawn>(chess::Color::Black)
    );


    auto blocked_bishop_moves =
        bishop.legal_moves(position, blocked_board);

    auto blocked_queen_moves =
        queen.legal_moves(position, blocked_board);


    std::cout << "\nBishop moves with obstacles: "
              << blocked_bishop_moves.size() << '\n';

    std::cout << "Queen moves with obstacles: "
              << blocked_queen_moves.size() << '\n';


    return 0;
}
