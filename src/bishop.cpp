#include "chess/bishop.hpp"
#include "chess/board.hpp"

#include <array>

namespace chess {

    std::vector<Position> Bishop::legal_moves(Position const& current_pos, Board const& board) const
    {
        std::vector<Position> possible_moves;
        //The bishop can move "unlimited" squares in the board, if it hits a enemy figure, it stops there. It cannot pass through own figures.
        //bishop directions
        std::array<Offset, 4> bishop_offsets{
            Offset{ 1, 1},
            Offset{ 1, -1},
            Offset{-1, 1},
            Offset{-1, -1}
        };
        //we run until we hit a figure or the edge of the board
        for (Offset const& offset : bishop_offsets)
        {
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
                    break;
                }
                target = target + offset;
            }
        }
        return possible_moves;
    }
}