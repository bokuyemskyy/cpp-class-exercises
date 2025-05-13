#include "battleship.hpp"

#include <iostream>

Board::Board() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = '-';
        }
    }
}

void Board::display() const {
    std::cout << "Current board is:\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 's') {
                std::cout << '-';
            } else {
                std::cout << board[i][j];
            }
        }
        std::cout << "\n";
    }
}

bool Board::placeShip(int x, int y) {
    if (board[x][y] == '-') {
        board[x][y] = 's';
        return true;
    }
    return false;
}

bool Board::checkHit(int x, int y) const { return (board[x][y] == 's' || board[x][y] == '!'); }

bool Board::verifyCoords(int x, int y) const {
    return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
};
void Board::markHit(int x, int y) {
    if (checkHit(x, y)) {
        board[x][y] = '!';
    } else {
        board[x][y] = 'x';
    }
}

bool Board::areAllSunk() const {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 's') {
                return false;
            }
        }
    }
    return true;
}

Battleships::Battleships() : remainingShips(NUM_SHIPS) {
    srand(time(nullptr));
    for (int i = 0; i < NUM_SHIPS; ++i) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        while (!board.placeShip(x, y)) {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
        }
    }
}

void Battleships::play() {
    int x, y;
    bool hit;

    while (!board.areAllSunk()) {
        board.display();
        std::cout << "Enter coordinates to BOMB (col and row) in range (0-" << BOARD_SIZE - 1
                  << "): ";
        std::cin >> y >> x;

        if (!board.verifyCoords(x, y)) {
            std::cout << "Wrong coordinates!\n";
            continue;
        }
        hit = board.checkHit(x, y);
        board.markHit(x, y);

        if (hit) {
            std::cout << "Hit! There was a ship!\n";
        } else {
            std::cout << "Miss! Try again.\n";
        }
    }

    std::cout << "Win!! You have sunk all the ships!\n";
}
