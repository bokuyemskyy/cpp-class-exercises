#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

bool areAnagrams(const std::vector<std::string>& words) {
    if (words.empty()) return true;

    std::string sortedReference = words[0];
    std::sort(sortedReference.begin(), sortedReference.end());

    for (size_t i = 1; i < words.size(); ++i) {
        std::string sortedWord = words[i];
        std::sort(sortedWord.begin(), sortedWord.end());

        if (sortedWord != sortedReference) return false;
    }

    return true;
}

int main() {
    std::ifstream file("words.txt");
    if (!file) {
        std::cerr << "Failed to open the file\n";
        return 1;
    }
    std::vector<std::string> words;
    std::string word;

    while (file >> word) {
        words.push_back(word);
    }

    if (areAnagrams(words)) {
        std::cout << "All words are anagrams." << std::endl;
    } else {
        std::cout << "Not all words are anagrams." << std::endl;
    }

    return 0;
}