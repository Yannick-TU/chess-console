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

};
}