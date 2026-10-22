#include <iostream>
#include "chess/position.hpp"

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

    return 0;

}