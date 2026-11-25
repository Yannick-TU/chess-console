#include "chess/chess_game.hpp"
#include "chess/bishop.hpp"
#include "chess/king.hpp"
#include "chess/knight.hpp"
#include "chess/pawn.hpp"
#include "chess/queen.hpp"
#include "chess/rook.hpp"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <stdexcept>

// promotion piece
namespace {
    std::unique_ptr<chess::Figure> make_promoted_figure(chess::Promo_piece promotion,
                                                        chess::Color color) {
        using namespace chess;

        switch (promotion) {
        case Promo_piece::Queen:
            return std::make_unique<Queen>(color);

        case Promo_piece::Rook:
            return std::make_unique<Rook>(color);

        case Promo_piece::Bishop:
            return std::make_unique<Bishop>(color);

        case Promo_piece::Knight:
            return std::make_unique<Knight>(color);
        }
        throw std::invalid_argument("Invalid promotion piece");
    }
} // namespace

namespace chess {

    Chess_game::Chess_game() {
        board_.put_initial_positions();
    }

    void Chess_game::update_castling_rights(Position const& from, Position const& to,
                                            Color moving_color, bool moving_king, bool moving_rook,
                                            Figure const* captured_figure) {
        // moving the king removes both castling rights
        if (moving_king) {
            if (moving_color == Color::White) {
                castling_rights_.white_kingside = false;
                castling_rights_.white_queenside = false;
            } else {
                castling_rights_.black_kingside = false;
                castling_rights_.black_queenside = false;
            }
        }

        // moving a rook removes the corresponding castling right
        if (moving_rook) {
            if (from == Position{0, 0})
                castling_rights_.white_queenside = false;

            if (from == Position{0, 7})
                castling_rights_.white_kingside = false;

            if (from == Position{7, 0})
                castling_rights_.black_queenside = false;

            if (from == Position{7, 7})
                castling_rights_.black_kingside = false;
        }

        // capturing a rook on its initial square removes its castling right.
        auto captured_rook = dynamic_cast<Rook const*>(captured_figure);
        if (captured_rook == nullptr)
            return;
        if (captured_rook->color() == Color::White) {
            if (to == Position{0, 0})
                castling_rights_.white_queenside = false;

            if (to == Position{0, 7})
                castling_rights_.white_kingside = false;
        } else {
            if (to == Position{7, 0})
                castling_rights_.black_queenside = false;

            if (to == Position{7, 7})
                castling_rights_.black_kingside = false;
        }
    }

    // is square attacked by a specific color?
    bool Chess_game::is_square_attacked(Position const& target, Color attack_color,
                                        Board const& board) const {
        for (int row = 0; row < board_size; ++row)
            for (int column = 0; column < board_size; ++column) {
                Position current{row, column};
                Figure const* figure = board.figure_at(current);
                if (figure == nullptr)
                    continue;

                if (figure->color() != attack_color)
                    continue;

                if (figure->attacks(current, target, board))
                    return true;
            }
        return false;
    }

    // Check whether a king is in check
    bool Chess_game::is_in_check(Color color, Board const& board) const {
        std::optional<Position> king_position;

        for (int row = 0; row < board_size; ++row)
            for (int column = 0; column < board_size; ++column) {
                Position current{row, column};
                Figure const* figure = board.figure_at(current);

                if (figure == nullptr || figure->color() != color)
                    continue;

                if (dynamic_cast<King const*>(figure) != nullptr) {
                    if (king_position)
                        throw std::logic_error("Multiple kings of one color");
                    king_position = current;
                }
            }

        if (!king_position)
            throw std::logic_error("King not found on board");
        Color opponent = color == Color::White ? Color::Black : Color::White;

        return is_square_attacked(*king_position, opponent, board);
    }

    // public check method
    bool Chess_game::is_in_check(Color color) const {
        return is_in_check(color, board_);
    }

    // check if player has at least one legal move
    bool Chess_game::has_legal_moves(Color color, Board const& board) const {
        for (int row = 0; row < board_size; ++row) {
            for (int column = 0; column < board_size; ++column) {
                Position from{row, column};
                Figure const* figure = board.figure_at(from);

                if (figure == nullptr || figure->color() != color)
                    continue;
                auto possible_moves = figure->legal_moves(from, board);

                for (Position const& to : possible_moves) {
                    // never capture a king
                    Figure const* target = board.figure_at(to);
                    if (dynamic_cast<King const*>(target) != nullptr)
                        continue;

                    // simulate board
                    Board sim = board;
                    sim.move_figure(from, to);
                    // is king not in check after
                    if (!is_in_check(color, sim))
                        return true;
                }
            }
        }

        return false;
    }

    // is the castle move valid?
    bool Chess_game::can_castle(Color color, bool kingside, Board const& board) const {
        int row = (color == Color::White) ? 0 : 7;
        Position king_from{row, 4};
        Position king_to = kingside ? Position{row, 6} : Position{row, 2};

        Position rook_from = kingside ? Position{row, 7} : Position{row, 0};

        Position rook_to = kingside ? Position{row, 5} : Position{row, 3};

        // check castling rights
        bool allowed = false;

        if (color == Color::White) {
            allowed = kingside ? castling_rights_.white_kingside : castling_rights_.white_queenside;
        } else {
            allowed = kingside ? castling_rights_.black_kingside : castling_rights_.black_queenside;
        }

        if (!allowed)
            return false;

        // check whether king and rook are on their initial squares
        auto king = dynamic_cast<King const*>(board.figure_at(king_from));
        auto rook = dynamic_cast<Rook const*>(board.figure_at(rook_from));

        if (king == nullptr || rook == nullptr)
            return false;

        if (king->color() != color || rook->color() != color)
            return false;

        // check whether the squares between king and rook are empty
        if (kingside) {
            if (board.is_occupied(Position{row, 5}) || board.is_occupied(Position{row, 6})) {
                return false;
            }
        } else {
            if (board.is_occupied(Position{row, 1}) || board.is_occupied(Position{row, 2}) ||
                board.is_occupied(Position{row, 3})) {
                return false;
            }
        }

        // the king must not currently be in check
        if (is_in_check(color, board))
            return false;

        // simulate king moving through the intermediate square
        Position transit = kingside ? Position{row, 5} : Position{row, 3};

        Board transit_board = board;
        transit_board.move_figure(king_from, transit);

        if (is_in_check(color, transit_board))
            return false;

        // simulate the complete castling move
        Board final_board = board;

        final_board.move_figure(king_from, king_to);
        final_board.move_figure(rook_from, rook_to);

        if (is_in_check(color, final_board))
            return false;

        return true;
    }

    // make a move
    bool Chess_game::make_move(Position const& from, Position const& to,
                               std::optional<Promo_piece> promotion) {
        // has the game already ended?
        Game_status current_status = status();
        if (current_status == Game_status::Checkmate || current_status == Game_status::Stalemate)
            return false;

        // we check for valid position, if there is a figure to be moved and if that figure has a
        // color matching the player
        if (!from.isValid() || !to.isValid() || from == to)
            return false;

        Figure const* moving_figure = board_.figure_at(from);
        if (moving_figure == nullptr)
            return false;

        if (moving_figure->color() != current_player_)
            return false;

        // prevent capturing of own figures
        Figure const* target_figure = board_.figure_at(to);
        if (target_figure != nullptr && target_figure->color() == moving_figure->color())
            return false;

        // prevent caputring the opponents king
        if (dynamic_cast<King const*>(target_figure) != nullptr)
            return false;

        bool moving_king = dynamic_cast<King const*>(moving_figure) != nullptr;
        bool moving_rook = dynamic_cast<Rook const*>(moving_figure) != nullptr;
        bool moving_pawn = dynamic_cast<Pawn const*>(moving_figure) != nullptr;

        Color moving_color = moving_figure->color();
        int column_difference = to.column() - from.column();

        // do we castle?
        bool castling = moving_king && to.row() == from.row() && std::abs(column_difference) == 2;

        if (castling) {
            bool kingside = column_difference > 0;
            if (!can_castle(current_player_, kingside, board_))
                return false;
        } else { // possible moves for that figure
            auto moves = moving_figure->legal_moves(from, board_);
            // is target square reachable?
            if (std::find(moves.begin(), moves.end(), to) == moves.end())
                return false;
        }

        // does a pawn promote?
        bool reaches_last_rank = moving_pawn && (to.row() == 0 || to.row() == 7);
        if (reaches_last_rank && !promotion.has_value())
            return false;
        if (!reaches_last_rank && promotion.has_value())
            return false;

        // execute a move on the board, including the special moves
        auto execute_move = [&](Board& board) -> std::unique_ptr<Figure> {
            // normal move
            auto captured_figure = board.move_figure(from, to);

            // castling
            if (castling) {
                Position rook_from =
                    column_difference > 0 ? Position{from.row(), 7} : Position{from.row(), 0};
                Position rook_to =
                    column_difference > 0 ? Position{from.row(), 5} : Position{from.row(), 3};
                board.move_figure(rook_from, rook_to);
            }

            // pawn promotion
            if (reaches_last_rank) {
                board.remove_figure(to);
                board.place_figure(to, make_promoted_figure(*promotion, moving_color));
            }

            return captured_figure;
        };

        // simulate board and check, if our own king is in check through the move -> invalid
        Board sim = board_;
        execute_move(sim);

        if (is_in_check(current_player_, sim))
            return false;

        // doing the move
        auto captured_figure = execute_move(board_);
        update_castling_rights(from, to, moving_color, moving_king, moving_rook,
                               captured_figure.get());
        // switch player
        current_player_ = current_player_ == Color::White ? Color::Black : Color::White;

        return true;
    }

    // current game status
    Game_status Chess_game::status() const {
        bool checked = is_in_check(current_player_, board_);

        bool moves_available = has_legal_moves(current_player_, board_);

        if (!moves_available) {
            if (checked)
                return Game_status::Checkmate;
            return Game_status::Stalemate;
        }
        if (checked)
            return Game_status::Check;

        return Game_status::InProgress;
    }
} // namespace chess