#include "chess/king.hpp"
#include "chess/board.hpp"

#include <array>
#include <cstdlib>

namespace chess {

    std::vector<Position> King::legal_moves(Position const& current_pos, Board const& board) const {
        std::vector<Position> possible_moves;
        // king can walk 1 square in any direction
        std::array<Offset, 8> king_offsets{Offset{-1, -1}, Offset{-1, 0}, Offset{-1, 1},
                                           Offset{0, -1},  Offset{0, 1},  Offset{1, -1},
                                           Offset{1, 0},   Offset{1, 1}};

        for (Offset const& offset : king_offsets) {
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
    // king attacks each square that is around him
    bool King::attacks(Position const& current_pos, Position const& target,
                       Board const& board) const {
        const int row_diff = std::abs(target.row() - current_pos.row());
        const int column_diff = std::abs(target.column() - current_pos.column());

        return row_diff <= 1 && column_diff <= 1 && (row_diff != 0 || column_diff != 0);
    }
} // namespace chess