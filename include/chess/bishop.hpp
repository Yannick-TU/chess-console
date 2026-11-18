#pragma once

#include "figure.hpp"

namespace chess {
    
class Bishop : public Figure {

    public:

    explicit Bishop (Color color)
        : Figure(color)
        { }
    
    //Symbol is defined by color
    char symbol () const override {
        return color() == Color::White ? 'B' : 'b';
    }

    //legal moves
    std::vector<Position> legal_moves(Position const& current_pos, Board const& board) const override;

    //clone
    std::unique_ptr<Figure> clone() const override
    {
        return std::make_unique<Bishop>(*this);
    }

    //what squares are attacked by this figure
    bool attacks(Position const& current_pos, Position const& target, Board const& board) const override;
    
};
}