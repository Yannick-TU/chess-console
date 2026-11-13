#include "figure.hpp"

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
    //std::vector<Position> legal_moves(Position const& current_pos, Board const& board) const override;
    std::vector<Position> legal_moves(
    Position const& current_pos,
    Board const& board
) const override
{
    return {};
}
};
}