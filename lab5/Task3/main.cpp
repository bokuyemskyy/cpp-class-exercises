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
    // initial
    std::vector<int> vec = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::cout << "Initial vector: ";
    printVector(vec);

    // std::sort
    std::ranges::sort(vec);
    std::cout << "Sorted vector: ";
    printVector(vec);

    // std::find
    auto it = std::ranges::find(vec, 9);
    if (it != vec.end())
        std::cout << "Found 9 in vec\n";
    else
        std::cout << "Not found 9 in vec\n";

    // std::accumulate
    std::cout << "Sum of elements in vector: " << std::accumulate(vec.begin(), vec.end(), 0)
              << "\n";

    // std::remove_if
    auto temp = std::ranges::remove_if(vec, [](int a) { return !(a % 2); });
    std::vector<int> odd(temp.begin(), temp.end());
    std::cout << "Odd vector: ";
    printVector(odd);
}