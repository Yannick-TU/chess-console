#pragma once

#include <iostream>
#include <string>

//Symbol and Color of a figure -> White King "K", Black pawn "p" etc.

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
