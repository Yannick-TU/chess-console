#pragma once

#include "chess/figure.hpp"

namespace chess {
    
    class Rook : public Figure {

        public:

        explicit Rook (Color color)
            : Figure(color)
            { }

        char symbol () const override {
            return color() == Color::White ? 'R' : 'r';
        }
        
        //legal move
        std::vector<Position> legal_moves(Position const& current_pos, Board const& board) const override;

        //clone
        std::unique_ptr<Figure> clone() const override
        {
            return std::make_unique<Rook>(*this);
        }

        //what squares are attacked by this figure
        bool attacks(Position const& current_pos, Position const& target, Board const& board) const override;
    };
}