#include <string>
#include <vector>
#include <iostream>
#include "add.cpp"

int main() {
    int localVariable = 5;
    {
        int blockVariable = 3;
    
        std::cout << "Block variable: " << blockVariable << std::endl;
        std::cout << "Local variable: " << localVariable << std::endl;
        std::cout << "Global variable: " << ::globalVariable << std::endl;
    }    
}