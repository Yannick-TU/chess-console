#include "chess/pawn.hpp"
#include "chess/board.hpp"

#include <array>

namespace chess {

    std::vector<Position> Pawn::legal_moves(Position const& current_pos, Board const& board) const
    {
        std::vector<Position> possible_moves;
        //Pawn can only move forwards hence if White Pawn -> row numbers increase, if black pawn row numbers decrease
        const int direction = color() == Color::White ? 1 : -1;
        const int starting_row = color() == Color::White ? 1 : 6;

        //moving forward
        Position one_step = current_pos + Offset{direction,0};
        if(one_step.isValid() && !board.is_occupied(one_step))
        {
            possible_moves.push_back(one_step);
            //if pawn hasnt moved yet it can move 2 squares at once
            if (current_pos.row() == starting_row)
            {
                Position two_steps = one_step + Offset{direction,0};
                if (one_step.isValid() && !board.is_occupied(two_steps))
                    possible_moves.push_back(two_steps);
            }
        }
        //diagonal captures and en passant
        std::array<int, 2> capture_directions{-1,1};
        auto ep_target = board.en_passant_target();

        for (int column_offset : capture_directions)
        {
            Position target = current_pos + Offset{direction, column_offset};
            if (!target.isValid())
                continue;
            Figure const* target_figure = board.figure_at(target);
            if(target_figure != nullptr)
            {
                if(target_figure->color() != color())
                    possible_moves.push_back(target);
                continue;
            }
            
            if(ep_target && target == *ep_target)
            {
                Position captured_pawn_position{current_pos.row(), target.column()};
                Figure const* adj_figure = board.figure_at(captured_pawn_position);
                //is an opposing Pawn?
                auto const* adj_pawn = dynamic_cast<Pawn const*>(adj_figure);
                if (adj_pawn != nullptr && adj_pawn->color() != color())
                    possible_moves.push_back(target);
            }
        }
        return possible_moves;
    }
}
 