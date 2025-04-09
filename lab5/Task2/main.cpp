#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
static void printVector(const std::vector<T>& vec) {
    for (const T& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

int main() {
    // initial
    std::vector<int> vec = {1, 6, 2, 7, 3, 5, 0, 9, 8, 4};
    std::cout << "Initial vector: ";
    printVector(vec);

    // ascending
    std::ranges::sort(vec, [](int a, int b) { return a < b; });
    std::cout << "Sorted ascending vector: ";
    printVector(vec);

    // descending
    std::ranges::sort(vec, [](int a, int b) { return a > b; });
    std::cout << "Sorted descending vector: ";
    printVector(vec);

    // even
    auto temp = std::ranges::remove_if(vec, [](int a) { return a % 2; });
    std::vector<int> even(temp.begin(), temp.end());
    std::cout << "Even vector: ";
    printVector(even);
}