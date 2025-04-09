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
    std::vector<int> vec;

    // adding
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::cout << "Vector after adding elements: ";
    printVector(vec);

    vec.emplace_back(4);
    vec.emplace_back(5);

    std::cout << "Vector after emplace_back: ";
    printVector(vec);

    // accessing
    std::cout << "First element: " << vec.front() << "\n";
    std::cout << "Last element: " << vec.back() << "\n";
    std::cout << "Element at index 2: " << vec[2] << "\n";

    // removing
    vec.pop_back();
    std::cout << "Vector after pop_back: ";
    printVector(vec);

    vec.erase(vec.begin() + 1);
    std::cout << "Vector after erase(vec.begin() + 1): ";
    printVector(vec);

    vec.erase(vec.begin(), vec.begin() + 1);
    std::cout << "Vector after erase(vec.begin(), vec.begin() + 1): ";
    printVector(vec);

    // iterating
    std::cout << "Iterating using range-based for loop: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    return 0;
}
