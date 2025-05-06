#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::ifstream in("input.txt");

    std::vector<int> v;
    int number;
    while (in >> number) {
        v.push_back(number);
    }

    std::vector<int> odd;
    std::ranges::copy_if(v, std::back_inserter(odd), [](int x) { return x % 2 != 0; });
    std::ranges::sort(odd);

    int sum = std::accumulate(odd.begin(), odd.end(), 0);

    std::cout << "Odd numbers (sorted): ";
    for (int x : odd) {
        std::cout << x << ' ';
    }
    std::cout << "\nSum: " << sum << '\n';
}
