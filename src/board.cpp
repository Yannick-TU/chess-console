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

    //implementing the functions defined for the chessboard
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

    std::unique_ptr<Figure> Board::move_figure(Position const& from, Position const& to)
    {
        if (!from.isValid() || !to.isValid())
            throw std::out_of_range("Positions are invalid");
        if (from == to)
            throw std::invalid_argument("Both fields are identical");
        
        auto& from_square = squares_[from.row()][from.column()];
        auto& to_square = squares_[to.row()][to.column()];

        if (!from_square)
            throw std::logic_error("No figure on that square");
        
        Figure const* moving_figure = from_square.get();
        //is one of our own figures on the target square?
        if(to_square && to_square->color() == moving_figure->color())
            throw std::logic_error("can't capture our own figure");
        
        //is this an en passant capture? Then our pawn captures on a different square that it that it than stands on
        auto const& moving_pawn = dynamic_cast<Pawn const*>(moving_figure);
        const int direction = moving_figure->color() == Color::White ? 1 : -1;

        //we caputre diagonally, left or right
        const bool is_en_passant = moving_pawn != nullptr && !to_square && en_passant_target_ && to == *en_passant_target_
        && to.row() == from.row() + direction && (to.column() == from.column() + 1 || to.column() == from.column() - 1);

        //what figure, if, have we captured
        std::unique_ptr<Figure> captured;
        
        if (is_en_passant)
        {
            Position capture_pos{from.row(), to.column()};
            auto& capture_square = squares_[capture_pos.row()][capture_pos.column()];

            //is this an enemys pawn?
            auto const& captured_pawn = dynamic_cast<Pawn const*>(capture_square.get());
            if (captured_pawn == nullptr || captured_pawn->color() == moving_pawn->color())
                throw std::logic_error("Invalid en passant capture");
            
            //removng the pawn
            captured = std::move(capture_square);
        }
        else
        {
            //normal capture
            captured = std::move(to_square);
        }
        //we move figure to target square and overwrite the old one
        to_square = std::move(from_square);



        en_passant_target_.reset();
        //set new en passant target after pawn double move, if this happend
        if (moving_pawn != nullptr)
        {
            const int starting_row = moving_pawn->color() == Color::White ? 1 : 6;
            if (from.row() == starting_row && to.row() == from.row() + 2 * direction && from.column() == to.column())
                en_passant_target_ = Position{(from.row() + to.row())/2, from.column()};
        }
        return captured;
    }
    //copy the whole board
    Board::Board(Board const& other)
    : en_passant_target_(other.en_passant_target_)
    {
        for (std::size_t row = 0; row < board_size; ++row)
            for (std::size_t column = 0; column < board_size; ++column)
                if (other.squares_[row][column])
                    squares_[row][column] = other.squares_[row][column]->clone();

    }
}

