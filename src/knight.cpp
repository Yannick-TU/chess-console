#include "chess/knight.hpp"
#include "chess/board.hpp"

#include <array>

namespace chess {

    std::vector<Position> Knight::legal_moves(Position const& current_pos, Board const& board) const
    {
        std::vector<Position> possible_moves;
        //knight walks in an L, can jump over other figures hence 8 possible movements
        std::array<Offset, 8> knight_offsets{
            Offset{2, 1},
            Offset{2, -1},
            Offset{-2, 1},
            Offset{-2,-1},
            Offset{ 1, 2},
            Offset{ 1, -2},
            Offset{-1, 2},
            Offset{-1, -2}
        };
    
        //check all possible positions, figure has to stay inbound of the board, cannot jump
        //onto square with same colored figure and if square is oocupied by different color figure, delete that figure
        for (Offset const& offset : knight_offsets) //const& -> no unecessary copies of offsets
        {
            //new position -> we use our overloaded + operator 
            Position target = current_pos + offset;
            //board boundaries
            if (!target.isValid())
                continue;

            //is square occupied and if so, is it an opponents figure?
            Figure const* target_figure = board.figure_at(target);
            if (target_figure == nullptr || target_figure->color() != color())
                possible_moves.push_back(target); 
        }
        return possible_moves;
    }
}