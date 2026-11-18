/*
Console Chess for two players on the same device
    Input: e2 e4 (start square and target square)
    Rochade: e1 g1 (moves the king two squares)
    Promotion: e7 e8 q (q=Queen, r=Rook, b=Bishop, n=Knight; if no input, it is asked for one)
    Commands: Help, End

    Compilation example:
    g++ -std=c++20 -Wall -Wextra -I include src/*.cpp main.cpp -o chess 
*/
 
#include "chess/chess_game.hpp"
#include "chess/pawn.hpp"
 
#include <cctype>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
 
using namespace chess;
 
namespace {
 
    void print_board(Board const& board)
    {
        std::cout << "\n    a b c d e f g h\n"
                  << "  +-----------------+\n";
        for (int row = board_size - 1; row >= 0; --row)
        {
            std::cout << row + 1 << " | ";
            for (int column = 0; column < board_size; ++column)
            {
                //print figure symbol or a dot
                Figure const* figure = board.figure_at(Position{row, column});
                std::cout << (figure ? figure->symbol() : '.') << ' ';
            }
            std::cout << "| " << row + 1 << '\n';
        }
        std::cout << "  +-----------------+\n"
                  << "    a b c d e f g h\n\n";
    }
 
    void print_help()
    {
        std::cout <<"Move: e2 e4\n"
                    "Castling: e1 g1 (move the king two squares)\n"
                    "Promotion: e7 e8 q (q=Queen, r=Rook, b=Bishop, n=Knight)\n"
                    "Commands: help, quit\n"
                    "Uppercase letters = White, lowercase letters = Black\n";
    }
 
    std::string to_lower(std::string text)
    {
        for (char& c : text)
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        return text;
    }
 
    std::string color_name(Color color)
    {
        return color == Color::White ? "White" : "Black";
    }
 
    std::optional<Promo_piece> parse_promotion(std::string const& text)
    {
        if (text == "q") return Promo_piece::Queen;
        if (text == "r") return Promo_piece::Rook;
        if (text == "b") return Promo_piece::Bishop;
        if (text == "n") return Promo_piece::Knight;
        return std::nullopt;
    }
 
    //does our own pawn promote?
    bool needs_promotion(Chess_game const& game, Position const& from, Position const& to)
    {
        auto pawn = dynamic_cast<Pawn const*>(game.board().figure_at(from));
        return pawn != nullptr && pawn->color() == game.current_player() && (to.row() == 0 || to.row() == board_size - 1);
    }
}
 
int main()
{
    Chess_game game;
 
    std::cout << "Chess for two players\n";
    print_help();
    print_board(game.board());
    
    //we run the game and check for inputs to move pieces from each player
    while (true)
    {
        //check game status
        Game_status status = game.status();
        if (status == Game_status::Checkmate)
        {
            Color winner = game.current_player() == Color::White ? Color::Black : Color::White;
            std::cout << "Checkmate, " << color_name(winner) << " wins.\n";
            break;
        }
        if (status == Game_status::Stalemate)
        {
            std::cout << "Stalemate, game is a remis.\n";
            break;
        }
        if (status == Game_status::Check)
            std::cout << color_name(game.current_player()) << " is in check\n";
 
        std::cout << color_name(game.current_player()) << " to move: ";

        //read input (text), transform it and validate the input
        std::string line;
        if (!std::getline(std::cin, line)) //input end (Strg+D / Strg+Z)
            break;
            
        //input string stream -> only reading
        std::istringstream input(to_lower(line));
        std::string from_text, to_text, promotion_text;
        input >> from_text >> to_text >> promotion_text;
 
        if (from_text.empty())
            continue;
        if (from_text == "end")
            break;
        if (from_text == "help")
        {
            print_help();
            continue;
        }
 
        //"e2e4" without space is allowed
        if (from_text.size() == 4 && to_text.empty())
        {
            to_text = from_text.substr(2, 2);
            from_text = from_text.substr(0, 2);
        }
 
        //text to position on board
        auto from = Position::fromAlgebraic(from_text);
        auto to = Position::fromAlgebraic(to_text);
        if (!from || !to)
        {
            std::cout << "Input incorrect. Example: e2 e4  (\"help\" for more)\n";
            continue;
        }
 
        //if a piece gets promoted
        std::optional<Promo_piece> promotion;
        if (!promotion_text.empty())
        {
            promotion = parse_promotion(promotion_text);
            if (!promotion)
            {
                std::cout << "Unknown promotion. Possible promotions: q, r, b, n\n";
                continue;
            }
        }
        else if (needs_promotion(game, *from, *to))
        {
            std::cout << "Promote into (q=Queen, r=Rook, b=Bishop, n=Knight): ";
            std::string answer;
            if (!std::getline(std::cin, answer))
                break;
            std::istringstream(to_lower(answer)) >> answer;
            promotion = parse_promotion(answer);
            if (!promotion)
            {
                std::cout << "Unknown promotion piece, turn terminated.\n";
                continue;
            }
        }
        //make a move
        if (!game.make_move(*from, *to, promotion))
        {
            std::cout << "Invalid move.\n";
            continue;
        }
 
        print_board(game.board());
    }
 
    std::cout << "Game ends.\n";
    return 0;
}
 