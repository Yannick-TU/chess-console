#pragma once

#include "chess/board.hpp"

namespace chess {

    // what is the current game state? Is the current game running or is a king in check, do we have
    // a checkmate or a stalemate?
    enum class Game_status { InProgress, Check, Checkmate, Stalemate };

    // a pawn can promote
    enum class Promo_piece { Queen, Rook, Bishop, Knight };

    // queen and kingside castling
    struct Castling_rights {
        bool white_kingside{true};
        bool white_queenside{true};

        bool black_kingside{true};
        bool black_queenside{true};
    };
    class Chess_game {

      private:
        // the current chess board
        Board board_;

        // whose players turn is it? Initially white
        Color current_player_{Color::White};

        // is a square attacked?
        bool is_square_attacked(Position const& target, Color attack_color,
                                Board const& board) const;

        // is the king in check?
        bool is_in_check(Color color, Board const& board) const;

        // has a player a legal move left or is there a stalemate?
        bool has_legal_moves(Color color, Board const& board) const;

        // can that player currently castle
        bool can_castle(Color color, bool kingside, Board const& board) const;

        void update_castling_rights(Position const& from, Position const& to, Color moving_color,
                                    bool moving_king, bool moving_rook,
                                    Figure const* captured_figure);

        // which castling moves are still allowed (set to false once king/rook moved or rook was
        // captured)
        Castling_rights castling_rights_{};

      public:
        // Constructor
        Chess_game();

        // doing a move
        bool make_move(Position const& from, Position const& to,
                       std::optional<Promo_piece> promotion = std::nullopt);

        // get current player
        Color current_player() const noexcept {
            return current_player_;
        }
        // get current board
        Board const& board() const noexcept {
            return board_;
        }

        // is a color/player in check?
        bool is_in_check(Color color) const;

        // get current game state
        Game_status status() const;

        // read-only access to the castling rights
        Castling_rights const& castling_rights() const noexcept {
            return castling_rights_;
        }
    };
} // namespace chess