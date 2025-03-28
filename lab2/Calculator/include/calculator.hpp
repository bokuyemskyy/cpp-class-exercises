#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <cstdint>
enum OperationSign : uint8_t { NONE, PLUS, MINUS, MULPTIPLY, DIVIDE };
class Operation {
   private:
    OperationSign operationSign = NONE;

   public:
    Operation(char operationChar) {
        switch (operationChar) {
            case '+':
                operationSign = PLUS;
                break;
            case '-':
                operationSign = MINUS;
                break;
            case '*':
                operationSign = MULPTIPLY;
                break;
            case '/':
                operationSign = DIVIDE;
                break;
            default:
                break;
        }
    }
    OperationSign getSign() { return operationSign; }
};

class Calculator {
   private:
    static float add(float leftOperand, float rightOperand);
    static float subtract(float leftOperand, float rightOperand);
    static float multiply(float leftOperand, float rightOperand);
    static float divide(float leftOperand, float rightOperand);

   public:
    static float calculate(float leftOperand, Operation operation, float rightOperand);
};

#endif