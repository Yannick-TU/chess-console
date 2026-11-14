#include "chess/rook.hpp"
#include "chess/board.hpp"

#include <array>

namespace chess {

    std::vector<Position> Rook::legal_moves(Position const& current_pos, Board const& board) const
    {
        std::vector<Position> possible_moves;
        //The rook can move "unlimited" squares in the board, if it hits a enemy figure, it stops there. It cannot pass through own figures.
        //Rook directions
        std::array<Offset, 4> rook_offsets{
            Offset{-1, 0},
            Offset{1, 0},
            Offset{0, 1},
            Offset{ 0, -1},
        };
        //we run until we hit a figure or the edge of the board
        for (Offset const& offset : rook_offsets)
        {
            //new position
            Position target = current_pos + offset;
            //board boundaries
            while (target.isValid())
            {
                //is square occupied and if so, is it an opponents figure?
                Figure const* target_figure = board.figure_at(target);
                if (target_figure == nullptr)
                    possible_moves.push_back(target); 
                else
                {
                    //we have a possible capture
                    if(target_figure->color() != color())
                        possible_moves.push_back(target);
                    //a figure is hit, one of our own or an opponents, either way we stop
                    break;
                }
                //move one square in the same direction
                target = target + offset;
            }
        }
        return possible_moves;
    }
}