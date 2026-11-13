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