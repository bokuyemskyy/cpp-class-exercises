#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main(int argc, char* argv[]) {
    std::filesystem::path absPath = std::filesystem::canonical(argv[0]).parent_path();
    std::ifstream file(absPath.string() + "/words.txt");
    if (!file) {
        std::cerr << "Failed to open the file!\n";
        return 1;
    }
    std::vector<std::string> words;
    std::string word;

    while (file >> word) {
        words.emplace_back(word);
    }

    if (std::ranges::is_sorted(words))
        std::cout << "The words are in alphabetical order!\n";
    else
        std::cout << "The words are not in alphabetical order!\n";
}