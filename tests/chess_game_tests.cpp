
#include <catch2/catch_test_macros.hpp>

#include "chess/chess_game.hpp"

TEST_CASE("Game validates the first move and changes the turn") {
    chess::Chess_game game;

    // Black cannot move first
    CHECK_FALSE(game.make_move(chess::Position{6, 4}, chess::Position{4, 4}));

    CHECK(game.current_player() == chess::Color::White);

    // White moves pawn from e2 to e4
    REQUIRE(game.make_move(chess::Position{1, 4}, chess::Position{3, 4}));

    CHECK(game.current_player() == chess::Color::Black);

    REQUIRE(game.board().figure_at(chess::Position{3, 4}) != nullptr);
    CHECK(game.board().figure_at(chess::Position{3, 4})->symbol() == 'P');

    CHECK(game.board().figure_at(chess::Position{1, 4}) == nullptr);
}
