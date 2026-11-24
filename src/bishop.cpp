#include "chess/bishop.hpp"
#include "chess/board.hpp"

#include <array>
#include <cstdlib>

namespace chess {

    std::vector<Position> Bishop::legal_moves(Position const& current_pos,
                                              Board const& board) const {
        std::vector<Position> possible_moves;
        // The bishop can move "unlimited" squares in the board, if it hits a enemy figure, it stops
        // there. It cannot pass through own figures. bishop directions
        std::array<Offset, 4> bishop_offsets{Offset{1, 1}, Offset{1, -1}, Offset{-1, 1},
                                             Offset{-1, -1}};

        // we run until we hit a figure or the edge of the board
        for (Offset const& offset : bishop_offsets) {
            Position target = current_pos + offset;
            // board boundaries
            while (target.isValid()) {
                // is square occupied and if so, is it an opponents figure?
                Figure const* target_figure = board.figure_at(target);
                if (target_figure == nullptr)
                    possible_moves.push_back(target);
                else {
                    // we have a possible capture
                    if (target_figure->color() != color())
                        possible_moves.push_back(target);
                    break;
                }
                target = target + offset;
            }
        }
        return possible_moves;
    }

    bool Bishop::attacks(Position const& current_pos, Position const& target,
                         Board const& board) const {
        if (current_pos == target || !current_pos.isValid() || !target.isValid())
            return false;

        const int row_diff = target.row() - current_pos.row();
        const int column_diff = target.column() - current_pos.column();

        // Bishop moves diagonally
        if (std::abs(row_diff) != std::abs(column_diff))
            return false;

        Offset step{(row_diff > 0) - (row_diff < 0), (column_diff > 0) - (column_diff < 0)};
        Position square = current_pos + step;

        while (square != target) {
            if (board.is_occupied(square))
                return false;
            square = square + step;
        }
        return true;
    }
} // namespace chess