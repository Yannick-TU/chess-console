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

};
}