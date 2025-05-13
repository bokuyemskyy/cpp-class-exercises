#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include <array>

const int BOARD_SIZE = 5;
const int NUM_SHIPS = 3;

class Board {
   private:
    std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> board;

   public:
    Board();
    void display() const;
    bool placeShip(int x, int y);
    bool checkHit(int x, int y) const;
    bool verifyCoords(int x, int y) const;
    void markHit(int x, int y);
    bool areAllSunk() const;
};

class Battleships {
   private:
    Board board;
    int remainingShips;

   public:
    Battleships();
    void play();
};

#endif
