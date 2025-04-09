#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

template <typename T>
static void printVector(const std::vector<T>& vec) {
    for (const T& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

int main() {
    // std::iota
    std::vector<int> vec(10);
    std::ranges::iota(vec, 1);
    std::cout << "Vector after std::iota: ";
    printVector(vec);

    // std::inner_product
    std::vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int product = std::inner_product(vec.begin(), vec.end(), vec2.begin(), 0);
    std::cout << "Inner product of vec and vec2: " << product << "\n";

    // std::partial_sum
    std::vector<int> partialSumVec = {1, 2, 3, 4, 5};
    std::partial_sum(partialSumVec.begin(), partialSumVec.end(), partialSumVec.begin());
    std::cout << "Partial sum of partialSumVec: ";
    printVector(partialSumVec);

    // std::adjacent_difference
    std::vector<int> diffVec = {10, 20, 30, 40, 50};
    std::adjacent_difference(diffVec.begin(), diffVec.end(), diffVec.begin());
    std::cout << "Adjacent difference of diffVec: ";
    printVector(diffVec);

    return 0;
}