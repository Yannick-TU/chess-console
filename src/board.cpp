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
    void Board::place_figure(Position const& position, std::unique_ptr<Figure> figure)
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
    //return pointer to a figure (const Board)
    Figure const* Board::figure_at(Position const& position) const
    {
        if (!position.isValid())
            throw std::out_of_range("Invalid board position");

        return squares_[position.row()][position.column()].get();
    }

    //check whether a square is occupied
    bool Board::is_occupied(Position const& position) const
    {
        return figure_at(position) != nullptr;
    }

    //remove figure from a square
    std::unique_ptr<Figure> Board::remove_figure(Position const& position)
    {
        if (!position.isValid())
            throw std::out_of_range("Invalid board position");
        return std::move(squares_[position.row()][position.column()]);
    }
    //figure counter
    std::size_t Board::figure_count() const
    {
        std::size_t count = 0;
        for (auto const& row : squares_)
        {
            for (auto const& square : row)
                if (square)
                    ++count;
        }
        return count;
    }

    //setup initial board with piece positions
    void Board::put_initial_positions() 
    {
        //clear all
        en_passant_target_.reset();
        for (auto& row : squares_)
            for(auto & square : row)
                square.reset();
        //placing the pawns
        for (int column = 0; column < board_size; ++column)
        {
            place_figure(Position{1, column}, std::make_unique<Pawn>(Color::White));
            place_figure(Position{6, column}, std::make_unique<Pawn>(Color::Black));
        }

        //placing the back ranks -> lambda function, this == &board (pointer to current board object), hence this->place_figure function
        auto place_back_rank = [this](int row, Color color)
        {
            place_figure(Position{row, 0}, std::make_unique<Rook>(color));
            place_figure(Position{row, 1}, std::make_unique<Knight>(color));
            place_figure(Position{row, 2}, std::make_unique<Bishop>(color));
            place_figure(Position{row, 3}, std::make_unique<Queen>(color));
            place_figure(Position{row, 4}, std::make_unique<King>(color));
            place_figure(Position{row, 5}, std::make_unique<Bishop>(color));
            place_figure(Position{row, 6}, std::make_unique<Knight>(color));
            place_figure(Position{row, 7}, std::make_unique<Rook>(color));
        };
        place_back_rank(0, Color::White);
        place_back_rank(7, Color::Black);
    }
    //en passant
    std::optional<Position> Board::en_passant_target() const
    {
        return en_passant_target_;
    }

    void Board::set_en_passant_target(std::optional<Position> target)
    {
        if (target && !target->isValid())
            throw std::out_of_range("Invalid en passant target");

        en_passant_target_ = target;
    }
}

