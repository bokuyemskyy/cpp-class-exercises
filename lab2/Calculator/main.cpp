#include <math.h>

#include <iostream>
#include <sstream>

#include "include/calculator.hpp"

int main() {
    Calculator calculator = Calculator();
    while (true) {
        std::string input;
        std::cout << R"(Enter an operation (use "+", "-", "*", "/", "exit" to exit): )";
        std::getline(std::cin, input);

        if (input == "exit") break;

        float leftOperand = NAN;
        float rightOperand = NAN;
        char operation = ' ';

        std::istringstream iss(input);
        if (!(iss >> leftOperand >> operation >> rightOperand)) {
            std::cout << "Invalid input. Please use <float><operator><float> format.\n";
            continue;
        }
        std::cout << "Result of the operation is "
                  << Calculator::calculate(leftOperand, Operation(operation), rightOperand) << '\n';
    }
}