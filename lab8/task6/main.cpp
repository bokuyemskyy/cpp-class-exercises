#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

const int ROWS = 2;
const int COLS = 4;

void display(const std::vector<std::vector<char>>& board,
             const std::vector<std::vector<bool>>& revealed) {
    std::cout << "    0 1 2 3\n";
    for (int i = 0; i < ROWS; ++i) {
        std::cout << " " << i << "  ";
        for (int j = 0; j < COLS; ++j) {
            if (revealed[i][j])
                std::cout << board[i][j] << " ";
            else
                std::cout << "* ";
        }
        std::cout << "\n";
    }
}

bool isSolved(const std::vector<std::vector<bool>>& revealed) {
    for (const auto& row : revealed)
        for (bool cell : row) {
            if (!cell) return false;
        }
    return true;
}

int main() {
    std::vector<char> cards = {'Q', 'Q', 'W', 'W', 'E', 'E', 'R', 'R'};

    std::srand(std::time(0));

    std::shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device()()));

    std::vector<std::vector<char>> board(ROWS, std::vector<char>(COLS));
    std::vector<std::vector<bool>> revealed(ROWS, std::vector<bool>(COLS, false));

    int k = 0;
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j) board[i][j] = cards[k++];

    while (!isSolved(revealed)) {
        display(board, revealed);

        int x1, y1, x2, y2;
        std::cout << "Enter first card (col row): ";
        std::cin >> y1 >> x1;
        std::cout << "Enter second card (col row): ";
        std::cin >> y2 >> x2;

        if (x1 == x2 && y1 == y2) {
            std::cout << "Pick two DIFFERENT cards!\n";
            continue;
        }

        if (revealed[x1][y1] || revealed[x2][y2]) {
            std::cout << "Card was already revealed. Pick other one.\n";
            continue;
        }

        revealed[x1][y1] = revealed[x2][y2] = true;
        display(board, revealed);

        if (board[x1][y1] == board[x2][y2]) {
            std::cout << "Cards matched!\n";
        } else {
            std::cout << "Cards did not match(\n";
            revealed[x1][y1] = revealed[x2][y2] = false;
        }
    }

    std::cout << "Win!! You matched all pairs.\n";
    return 0;
}
