#pragma once 

#include <vector>
#include "chess/position.hpp"
#include <memory>

//symbol Interface and Color of a figure -> White King "K", Black pawn "p" etc.
//abstract base class for the concrete classes like King etc.


namespace chess {
    // Forward declaration
    class Board;

    enum class Color {
        White,
        Black
    };
    class Figure {

        Color color_; 

        public: 
        //Constructor explicit because we dont want an implicit conversion from Color to Figure
        explicit Figure (Color color) 
            : color_(color)
            { }
        virtual ~Figure() = default;

        Color color() const {
            return color_;
        }
        //Return the symbol of the figure
        virtual char symbol() const = 0;

        //is a move legal? Given a current position and the current state of the board
        virtual std::vector<Position> legal_moves(Position const& current_pos, Board const& board) const = 0;

        //create a copy of a concrete figure
        virtual std::unique_ptr<Figure> clone() const = 0;

        //what figure attacks which squares
        virtual bool attacks(Position const& current_pos, Position const& traget, Board const& board) const = 0;
    };
}
