#include "chess/board.hpp"
#include "chess/king.hpp"
#include "chess/queen.hpp"
#include "chess/rook.hpp"
#include "chess/bishop.hpp"
#include "chess/knight.hpp"
#include "chess/pawn.hpp"

#include <stdexcept>
#include <utility>

namespace chess {
//Implementing the functions defined for the chessboard
    void Board::place_figure(Position &const position, std::unique_ptr<Figure> figure)
    {
        if (!position.isValid())
            throw std::out_of_range("Board position is not valid");
        if (!figure)
            throw std::invalid_argument("Cannot place a null figure");
        
        auto& square = squares_[position.row()][position.column()];

        if (square)
            throw std::logic_error("Position is occupied");

        //Move ownership of figure to board, pointer is now empty
        square = std::move(figure);
    }
    Figure* const Board::figure_at (Position &const position)
    {
        if (!position.isValid())
            throw std::out_of_range("Invalid board position");
        return squares_[position.row()][position.column()].get();
    }




    
}

