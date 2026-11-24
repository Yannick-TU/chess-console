#pragma once

#include "figure.hpp"

namespace chess {
    
    class Queen : public Figure {

        public:

        explicit Queen (Color color)
            : Figure(color)
            { }
        

        char symbol () const override {
            return color() == Color::White ? 'Q' : 'q';
        }
        
        //legal move
        std::vector<Position> legal_moves(Position const& current_pos, Board const& board) const override;

        //clone
        std::unique_ptr<Figure> clone() const override
        {
            return std::make_unique<Queen>(*this);
        }

        //what squares are attacked by this figure
        bool attacks(Position const& current_pos, Position const& target, Board const& board) const override;

    };
}