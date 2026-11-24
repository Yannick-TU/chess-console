#include "chess/queen.hpp"
#include "chess/board.hpp"

#include <array>
#include <cstdlib>

namespace chess {

    std::vector<Position> Queen::legal_moves(Position const& current_pos,
                                             Board const& board) const {
        std::vector<Position> possible_moves;
        // Queen can move both horizontal, vertical and diagonal
        std::array<Offset, 8> queen_offsets{
            Offset{-1, 1}, Offset{1, -1}, Offset{1, 1}, Offset{-1, -1},
            Offset{-1, 0}, Offset{0, -1}, Offset{1, 0}, Offset{0, 1},
        };
        // we run until we hit a figure or the edge of the board
        for (Offset const& offset : queen_offsets) {
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
    bool Queen::attacks(Position const& current_pos, Position const& target,
                        Board const& board) const {
        if (current_pos == target || !current_pos.isValid() || !target.isValid())
            return false;

        const int row_diff = target.row() - current_pos.row();
        const int column_diff = target.column() - current_pos.column();

        const bool straight = row_diff == 0 || column_diff == 0;
        const bool diagonal = std::abs(row_diff) == std::abs(column_diff);

        if (!straight && !diagonal)
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