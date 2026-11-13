#include "chess/figure.hpp"
#include "chess/position.hpp"
namespace chess {
    
class King : public Figure {

    public:
    //Konstruktor, King is a Figure, call base class
    explicit King (Color color)
        : Figure(color)
        { }
    
    //Symbol is defined by color
    char symbol () const override {
        return color() == Color::White ? 'K' : 'k';
    }
    //legal move
    std::vector<Position> legal_moves(Position const& current_pos, Board const& board) const override;
};
}