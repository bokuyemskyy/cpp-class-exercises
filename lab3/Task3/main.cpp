#include <string>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    int arr[5] = {1, 2, 3, 4, 5};

    std::cout << "Vector: ";
    for (auto& elem : vec) {
        elem *= 2;
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Array: ";
    for (auto& elem : arr) {
        elem *= 2;
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}