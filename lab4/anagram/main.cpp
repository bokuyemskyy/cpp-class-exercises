#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

bool areAnagrams(const std::vector<std::string>& words) {
    if (words.empty()) return true;

    std::string sortedReference = words[0];
    std::ranges::sort(sortedReference);

    for (size_t i = 1; i < words.size(); ++i) {
        std::string sortedWord = words[i];
        std::ranges::sort(sortedWord);

        if (sortedWord != sortedReference) return false;
    }

    return true;
}

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

    if (areAnagrams(words)) {
        std::cout << "All words are anagrams.\n";
    } else {
        std::cout << "Not all words are anagrams.\n";
    }

    return 0;
}