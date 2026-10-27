#include "figure.hpp"

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

};
}