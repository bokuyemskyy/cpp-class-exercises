#include "game.hpp"

void Board::display() const {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << toChar(grid[i][j]);
            if (j < BOARD_SIZE - 1) std::cout << " | ";
        }
        std::cout << "\n";
        if (i < BOARD_SIZE - 1) std::cout << "--+---+--\n";
    }
}
bool Board::placeSymbol(int row, int col, Symbol symbol) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) return false;
    if (grid[row][col] != Symbol::NONE) return false;

    grid[row][col] = symbol;
    return true;
};
bool Board::checkWin(Symbol symbol) const {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        return ((grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) ||
                (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol));
    }

    return (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) ||
           (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol);
};
bool Board::isFull() const {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (grid[i][j] == Symbol::NONE) return false;
    return true;
};
void Game::play() {
    int row, col;
    while (true) {
        board.display();
        std::cout << currentPlayer->getName() << " (" << toChar(currentPlayer->getSymbol())
                  << ") enters move (col and row): ";
        std::cin >> col >> row;

        if (!board.placeSymbol(row, col, currentPlayer->getSymbol())) {
            std::cout << "Invalid move\n";
            continue;
        }

        if (board.checkWin(currentPlayer->getSymbol())) {
            board.display();
            std::cout << currentPlayer->getName() << " won!\n";
            break;
        }

        if (board.isFull()) {
            board.display();
            std::cout << "Draw!\n";
            break;
        }

        switchPlayer();
    }
};
int main() {
    Game game;
    game.play();
    return 0;
}