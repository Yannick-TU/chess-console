#pragma once

#include <array>
#include <cstddef>
#include <memory>
#include "chess/figure.hpp"
#include "chess/position.hpp"

//Creating the chessboard. We have 8 x 8 squares (board_size) each object of type figure is designated
//a position in our array squares_ i.e. white pawn P on squares_[0][4]

namespace chess {

class Board {

    //Chessboard containing pointers to figures 
    std::array<std::array<std::unique_ptr<Figure>,board_size>,board_size> squares_{};

    public:

    //Constructor
    Board() = default;

    //Standard functions -> place, remove, set and initial setup
    void putInitial_positions(); 

    //place a figure on a specific square
    void place_figure (Position &const position, std::unique_ptr<Figure> figure);

    //remove a figure from a square
    std::unique_ptr<Figure> remove_figure (Position &const position);

    //return a pointer to the figure on a square
    Figure* const figure_at (Position &const position);

    //is a figure on that square?
    bool is_occupied (Position const& position) const;

    //count all figures on the board
    size_t figure_count() const;

};
}