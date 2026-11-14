#include "chess/queen.hpp"
#include "chess/board.hpp"

#include <array>

namespace chess {

    std::vector<Position> Queen::legal_moves(Position const& current_pos, Board const& board) const
    {
        std::vector<Position> possible_moves;
        //Queen can move both horizontal, vertical and diagonal
        std::array<Offset, 8> queen_offsets{
            Offset{-1, 1},
            Offset{1, -1},
            Offset{1, 1},
            Offset{-1,-1},
            Offset{-1, 0},
            Offset{0, -1},
            Offset{1, 0},
            Offset{0, 1},
        };
        //we run until we hit a figure or the edge of the board
        for (Offset const& offset : queen_offsets)
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