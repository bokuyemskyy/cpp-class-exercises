#include "puzzle.hpp"

Puzzle::Puzzle() {
    std::array<int, SIZE * SIZE> buffer;

    for (int i = 0; i < SIZE * SIZE; ++i) buffer[i] = i;
    std::shuffle(buffer.begin(), buffer.end(), std::mt19937(std::random_device()()));

    int k = 0;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = buffer[k++];
            if (board[i][j] == 0) {
                emptyX = i;
                emptyY = j;
            }
        }
}

void Puzzle::display() const {
    std::cout << "\n+----+----+----+----+\n";
    for (const auto& row : board) {
        for (int val : row) {
            if (val == 0)
                std::cout << "|    ";
            else
                std::cout << "| " << (val < 10 ? " " : "") << val << " ";
        }
        std::cout << "|\n+----+----+----+----+\n";
    }
}

bool Puzzle::move(char direction) {
    int dx = 0, dy = 0;
    if (direction == 'w')
        dx = -1;
    else if (direction == 's')
        dx = 1;
    else if (direction == 'a')
        dy = -1;
    else if (direction == 'd')
        dy = 1;
    else
        return false;

    int newx = emptyX + dx, newy = emptyY + dy;
    if (newx < 0 || newx >= SIZE || newy < 0 || newy >= SIZE) return false;

    std::swap(board[emptyX][emptyY], board[newx][newy]);
    emptyX = newx;
    emptyY = newy;
    return true;
}

bool Puzzle::isSolved() const {
    int expected = 1;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j, expected++)
            if ((i == SIZE - 1 && j == SIZE - 1 && board[i][j] != 0) ||
                (i != SIZE - 1 || j != SIZE - 1) && board[i][j] != expected)
                return false;
    return true;
}
