#include <iostream>

static constexpr int incrementedValue(int i) { return i + 1; }

int incrementedValueRealtime(int i) { return i + 1; }

int main() {
    constexpr int i = 10;
    constexpr char c = 'c';

    constexpr int value1 = incrementedValue(i);
    int value2 = incrementedValueRealtime(i);

    std::cout << "value1: " << value1 << std::endl;
    std::cout << "value2: " << value2 << std::endl;

    if (value1 != value2) {
        std::cout << "Comparison failed" << std::endl;
    }
}