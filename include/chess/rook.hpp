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

};
}