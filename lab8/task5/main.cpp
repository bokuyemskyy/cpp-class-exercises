#include "puzzle.hpp"

int main() {
    Puzzle puzzle;

    char move;

    while (!puzzle.isSolved()) {
        puzzle.display();
        std::cout << "Enter move (w/a/s/d): ";
        std::cin >> move;
        puzzle.move(move);
    }
    puzzle.display();

    std::cout << "You solved the puzzle!!\n";
    return 0;
}
