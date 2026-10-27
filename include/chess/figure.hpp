#pragma once //Gibt an, dass der Compiler die Headerdatei nur einmal enthält, wenn eine Quellcodedatei kompiliert wird. https://learn.microsoft.com/de-de/cpp/preprocessor/once?view=msvc-170

#include <iostream>
#include <string>

//Symbol Interface and Color of a figure -> White King "K", Black pawn "p" etc.
//Abstract base class fpr the concrete classes like King etc.


namespace chess {

    enum class Color {
        White,
        Black
    };
class Figure {

    Color color_; 

    public: 
    //Constructor explicit because we dont want an implicit conversion from Color to Figure
    explicit Figure (Color color) 
        : color_(color)
        { }
    //Destructor, we have multiple different Figures later
    virtual ~Figure() = default;

    //Simple getter
    Color color() const {
        return color_;
    }
    //Return the symbol of the figure
    virtual char symbol () const = 0;

};
}
