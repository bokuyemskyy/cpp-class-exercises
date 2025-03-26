#include <iostream>
#include <sstream>

#include "include/calculator.hpp"

int main(int argc, char *argv[]) {
    Calculator calculator = Calculator();
    while (true) {
        std::string input;
        std::cout << "Enter an operation (use \"+\", \"-\", \"*\", \"/\", \"exit\" to exit): ";
        std::getline(std::cin, input);

        if (input == "exit") break;

        float a, b;
        char op;
        std::istringstream iss(input);
        if (!(iss >> a >> op >> b)) {
            std::cout << "Invalid input. Please use <float><operator><float> format." << std::endl;
            continue;
        }
        std::cout << "Result of the operation is " << calculator.calculate(a, op, b) << std::endl;
    }
}