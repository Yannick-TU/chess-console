#include "chess/knight.hpp"
#include "chess/board.hpp"

#include <array>
#include <cstdlib>

namespace chess {

    std::vector<Position> Knight::legal_moves(Position const& current_pos,
                                              Board const& board) const {
        std::vector<Position> possible_moves;
        // knight walks in an L, can jump over other figures hence 8 possible movements
        std::array<Offset, 8> knight_offsets{Offset{2, 1},   Offset{2, -1}, Offset{-2, 1},
                                             Offset{-2, -1}, Offset{1, 2},  Offset{1, -2},
                                             Offset{-1, 2},  Offset{-1, -2}};

        // check all possible positions, figure has to stay inbound of the board, cannot jump
        // onto square with same colored figure and if square is oocupied by different color figure,
        // delete that figure
        for (Offset const& offset : knight_offsets) {
            // new position
            Position target = current_pos + offset;
            // board boundaries
            if (!target.isValid())
                continue;

            // is square occupied and if so, is it an opponents figure?
            Figure const* target_figure = board.figure_at(target);
            if (target_figure == nullptr || target_figure->color() != color())
                possible_moves.push_back(target);
        }
        return possible_moves;
    }

    bool Knight::attacks(Position const& current_pos, Position const& target, Board const&) const {
        const int row_diff = std::abs(target.row() - current_pos.row());
        const int column_diff = std::abs(target.column() - current_pos.column());

        return (row_diff == 2 && column_diff == 1) || (row_diff == 1 && column_diff == 2);
    }
} // namespace chess