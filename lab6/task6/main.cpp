#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
int main(int argc, char* argv[]) {
    std::filesystem::path path = std::filesystem::canonical(argv[0]).parent_path();
    std::string filepath = path.string() + "/file";
    std::ifstream file(filepath);

    std::vector<int> numbers;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            numbers.push_back(stoi(line));
        }
        file.close();
    }

    std::vector<int> oddNumbers;
    std::ranges::copy_if(numbers, std::back_inserter(oddNumbers), [](int x) { return x % 2 != 0; });
    std::ranges::sort(oddNumbers);

    int sum = std::accumulate(oddNumbers.begin(), oddNumbers.end(), 0);

    std::cout << "Odd numbers (sorted): ";
    for (int x : oddNumbers) {
        std::cout << x << ' ';
    }
    std::cout << "\nSum of odd numbers: " << sum << '\n';
}