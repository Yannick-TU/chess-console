#include "figure.hpp"

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

};
}