#include "chess/figure.hpp"
#include "chess/king.hpp"
#include "chess/queen.hpp"
#include "chess/rook.hpp"
#include "chess/bishop.hpp"
#include "chess/knight.hpp"
#include "chess/pawn.hpp"
#include "chess/position.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <array>


//Helper for color disp.
const char* colorName(chess::Color color)
{
    return color == chess::Color::White ? "White" : "Black";
}

int main() {
    using namespace chess;

    //Auto: compiler works out the type
    auto position = Position::fromAlgebraic("e4");
    if (position) {
        std::cout << "Row: " << position->row() << ", Column: " << position->column() << std::endl;
    }

    auto position_2 = position->toAlgebraic();
    if (position_2)     
        std::cout << "Position_2" << *position_2 << std::endl;

    Position p1{3,4};
    Position p2{3,4};

    std::cout << "Equal: " << (p1 == p2) << std::endl;
    std::cout << "Not equal: " << (p1 != p2) << std::endl;

      // Test 4: Offset
    Position e2{1, 4};
    Position e4{3, 4};

    Offset movement = e4 - e2;

    std::cout << "Offset: "
              << movement.row << ", "
              << movement.column << '\n';

    // Test 5: Add offset
    Position result = e2 + movement;

    std::cout << "Correct result: "
              << (result == e4) << '\n';

    // Test 6: Invalid notation
    auto invalid = Position::fromAlgebraic("z9");

    std::cout << "Invalid notation: "
              << !invalid << '\n';


    //Create container for figures using the base class, we test each figure type
    std::vector<std::unique_ptr<Figure>> figures;

    //Create one black and one white King
    figures.push_back(std::make_unique<King>(Color::White));
    figures.push_back(std::make_unique<King>(Color::Black));

    for (std::size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure " << figures[i]->symbol() << " Color: " << colorName(figures[i]->color()) << std::endl;
    }

    return 0;

}