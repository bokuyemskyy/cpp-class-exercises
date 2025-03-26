#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

class Calculator {
   private:
    float add(float a, float b);
    float subtract(float a, float b);
    float multiply(float a, float b);
    float divide(float a, float b);

   public:
    float calculate(float a, char op, float b);
};

#endif