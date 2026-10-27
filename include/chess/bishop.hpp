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

};
}