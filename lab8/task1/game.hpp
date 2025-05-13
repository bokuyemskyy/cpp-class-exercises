#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>

enum class Symbol : uint8_t { NONE, X, O };

inline static char toChar(Symbol symbol) {
    switch (symbol) {
        case Symbol::X:
            return 'X';
        case Symbol::O:
            return 'O';
        default:
            return ' ';
    }
}

constexpr int BOARD_SIZE = 3;
constexpr int SQUARE_NB = BOARD_SIZE * BOARD_SIZE;

class Player {
   private:
    Symbol m_symbol;
    std::string m_name;

   public:
    Player(Symbol symbol, std::string name) : m_symbol(symbol), m_name(std::move(name)) {};
    [[nodiscard]] Symbol getSymbol() const { return m_symbol; }
    [[nodiscard]] const std::string& getName() const { return m_name; }
};

class Board {
   private:
    std::array<std::array<Symbol, BOARD_SIZE>, BOARD_SIZE> grid{};

   public:
    Board() {
        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j) grid[i][j] = Symbol::NONE;
    };
    void display() const;
    bool placeSymbol(int row, int col, Symbol symbol);
    [[nodiscard]] bool checkWin(Symbol symbol) const;
    [[nodiscard]] bool isFull() const;
};

class Game {
   private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;

    void switchPlayer() { currentPlayer = (currentPlayer == &player1) ? &player2 : &player1; };

   public:
    Game()
        : player1(Symbol::X, "Player 1"), player2(Symbol::O, "Player 2"), currentPlayer(&player1) {}
    void play();
};
