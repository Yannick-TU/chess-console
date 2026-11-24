#pragma once

#include "figure.hpp"

namespace chess {
    
    class Pawn : public Figure {

        public:

        explicit Pawn (Color color)
            : Figure(color)
            { }
        
        //Symbol is defined by color
        char symbol () const override {
            return color() == Color::White ? 'P' : 'p';
        }
        
        //legal move
        std::vector<Position> legal_moves(Position const& current_pos, Board const& board) const override;

        //clone
        std::unique_ptr<Figure> clone() const override
        {
            return std::make_unique<Pawn>(*this);
        }
        
        //what squares are attacked by this figure
        bool attacks(Position const& current_pos, Position const& target, Board const& board) const override;

    };
}