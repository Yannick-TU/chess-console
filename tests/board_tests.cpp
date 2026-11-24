
#include <catch2/catch_test_macros.hpp>

#include "chess/board.hpp"

TEST_CASE("Board initializes the standard 32 pieces") {
    chess::Board board;
    board.put_initial_positions();

    CHECK(board.figure_count() == 32);

    REQUIRE(board.figure_at(chess::Position{0, 4}) != nullptr);
    CHECK(board.figure_at(chess::Position{0, 4})->symbol() == 'K');

    REQUIRE(board.figure_at(chess::Position{1, 4}) != nullptr);
    CHECK(board.figure_at(chess::Position{1, 4})->symbol() == 'P');

    CHECK(board.figure_at(chess::Position{3, 4}) == nullptr);
}
