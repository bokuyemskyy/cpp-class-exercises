#include "../include/calculator.hpp"

float Calculator::add(float a, float b) { return a + b; }
float Calculator::subtract(float a, float b) { return a - b; }
float Calculator::multiply(float a, float b) { return a * b; }
float Calculator::divide(float a, float b) { return a / b; }

float Calculator::calculate(float a, char op, float b) {
    switch (op) {
        case '+':
            return add(a, b);
        case '-':
            return subtract(a, b);
        case '*':
            return multiply(a, b);
        case '/':
            return divide(a, b);
        default:
            return 0;
    }
}