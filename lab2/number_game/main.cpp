#include <cstdlib>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    bool running = true;
    while (running) {
        int targetNumber = rand() % 100 + 1;
        int tries = 0;

        std::string input;
        std::cout
            << "I thought of a number between 1 and 100. Try to guess it! (\"exit\" to exit)\n"
               "Enter your guess: ";

        while (true) {
            int guess;
            std::getline(std::cin, input);
            if (input == "exit") {
                running = false;
                break;
            }

            if (!(std::istringstream(input) >> guess)) {
                std::cout << "Invalid input. Please enter an integer." << std::endl;
                continue;
            }

            if (guess == targetNumber) {
                std::cout << "Congratulations! You guessed the number " << targetNumber << " in "
                          << tries << " tries." << std::endl
                          << std::endl;
                break;
            } else if (guess < targetNumber) {
                std::cout << "Your guess is too low. Try again." << std::endl;
            } else {
                std::cout << "Your guess is too high. Try again." << std::endl;
            }

            tries++;
        }
    }
}