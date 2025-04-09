#include "../include/calculator.hpp"

float Calculator::add(float leftOperand, float rightOperand) { return leftOperand + rightOperand; }
float Calculator::subtract(float leftOperand, float rightOperand) {
    return leftOperand - rightOperand;
}
float Calculator::multiply(float leftOperand, float rightOperand) {
    return leftOperand * rightOperand;
}
float Calculator::divide(float leftOperand, float rightOperand) {
    return leftOperand / rightOperand;
}

float Calculator::calculate(float leftOperand, Operation operation, float rightOperand) {
    switch (operation.getSign()) {
        case PLUS:
            return add(leftOperand, rightOperand);
        case MINUS:
            return subtract(leftOperand, rightOperand);
        case MULPTIPLY:
            return multiply(leftOperand, rightOperand);
        case DIVIDE:
            return divide(leftOperand, rightOperand);
        default:
            return 0;
    }
}