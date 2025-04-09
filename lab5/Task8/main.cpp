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
    std::vector<int> vec = {5, 2, 8, 3, 1, 4, 7, 6};

    std::ranges::sort(vec, [](int a, int b) { return a < b; });

    std::cout << "Sorted vector: ";
    printVector(vec);

    int sum = std::accumulate(vec.begin(), vec.end(), 0,
                              [](int accumulator, int current) { return accumulator + current; });

    std::cout << "Sum of elements: " << sum << "\n";

    return 0;
}
