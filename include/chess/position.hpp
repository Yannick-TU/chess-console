#pragma once

#include <iostream>
#include <string>
#include <optional>

namespace chess {
    inline constexpr int board_size = 8;

    //Offset between two positions
    struct Offset {
        int row{};
        int column{};

        friend bool operator == (Offset const &, Offset const &) = default;
    };


class Position {

    // row number on the chessboard
    int row_;
    // column number on the chessboard
    int column_;

public:
    /*** Constructors ***/
    Position()
    { }

    // Init. of coordinates/position, e.g. (1,4)
    Position(int row, int column)
        : row_(row),
          column_(column)
    {}
    
    /*** Get Methods ***/
    int column() const
    { return column_; }
    
    int row() const
    { return row_; }

    /*** Quick valdiation ***/
    bool isValid() const {
        return row_ >= 0 && row_ < board_size && column_ >= 0 && column_ < board_size;
    }

    /*** Conversion from Algebraic to position notation and vice versa ***/

    static std::optional<Position> fromAlgebraic (std::string const & str) {
        if (str.size() != 2) 
            return std::nullopt;
        
        char letter = str[0];
        char number = str[1];

        // Check if inputs are valid 
        if (letter < 'a' || letter > 'h' || number <'1' || number > '8')
            return std::nullopt;

        return Position{letter - 'a', number - '1'};
    }

    std::optional<std::string> toAlgebraic () const {
        if (!isValid()) 
            return std::nullopt;
        
        std::string str;
        
        str += static_cast<char>(column_ + 'a');
        str += static_cast<char>(row_ + '1');

        return str;
    }

    /*** Overloading some operators to compute new positions after a move ***/

    friend bool operator==(Position const&, Position const&) = default;

    //Substract two positions -> the offeset
    friend Offset operator - (Position const & first, Position const & second){
        return {first.row_ - second.row_, first.column_ - second.column_};
    }
    //Add an offset to a position
    friend Position operator + (Position const & pos, Offset const & offset){
        return {pos.row_ + offset.row, pos.column_ + offset.column};
    }

};
}
