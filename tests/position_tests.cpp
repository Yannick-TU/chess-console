
#include <catch2/catch_test_macros.hpp>

#include "chess/position.hpp"

TEST_CASE("Position converts algebraic coordinates") {
    auto position = chess::Position::fromAlgebraic("e4");

    REQUIRE(position.has_value());

    CHECK(position->row() == 3);
    CHECK(position->column() == 4);

    auto algebraic = position->toAlgebraic();

    REQUIRE(algebraic.has_value());
    CHECK(*algebraic == "e4");

    CHECK_FALSE(chess::Position::fromAlgebraic("z9").has_value());
}
