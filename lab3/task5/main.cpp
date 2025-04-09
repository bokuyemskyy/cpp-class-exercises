#include <iostream>

int main() {
    int i = 1;
    double d = 5.5;
    char charArray[5] = {'a', 'b', 'c', 'd', 'e'};

    std::cout << "int size: " << sizeof(i) << std::endl;
    std::cout << "double size: " << sizeof(d) << std::endl;
    std::cout << "char array size: " << sizeof(charArray) << std::endl;
    std::cout << "char array length: " << sizeof(charArray) / sizeof(char) << std::endl;
}