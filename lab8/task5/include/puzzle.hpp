#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <algorithm>
#include <array>
#include <ctime>
#include <iostream>
#include <random>

const int SIZE = 4;
using BoardArray = std::array<std::array<int, SIZE>, SIZE>;

class Puzzle {
   private:
    BoardArray board;
    int emptyX, emptyY;

   public:
    Puzzle();
    void display() const;
    bool move(char dir);
    [[nodiscard]] bool isSolved() const;
};

#endif
