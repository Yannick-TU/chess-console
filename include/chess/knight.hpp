#pragma once

#include "chess/figure.hpp"
#include "chess/position.hpp"


//(K)night
namespace chess {
    
class Knight : public Figure {

    public:

    explicit Knight (Color color)
        : Figure(color)
        { }
    
    char symbol () const override {
        return color() == Color::White ? 'N' : 'n';
    }
    //legal move
    std::vector<Position> legal_moves(Position const& current_pos, Board const& board) const override;

    //clone
    std::unique_ptr<Figure> clone() const override
    {
        return std::make_unique<Knight>(*this);
    }

    //what squares are attacked by this figure
    bool attacks(Position const& current_pos, Position const& target, Board const& board) const override;
};
}