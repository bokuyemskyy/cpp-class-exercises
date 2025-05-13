#include <array>
#include <iostream>
#include <string>
#include <unordered_set>

#include "pics.hpp"

class Hangman {
   private:
    std::string targetWord;
    std::unordered_set<char> guessedChars;
    std::string currentWord;
    int lives;

    void update(char guess) {
        bool correct = false;
        for (size_t i = 0; i < targetWord.size(); ++i) {
            if (targetWord[i] == guess) {
                currentWord[i] = guess;
                correct = true;
            }
        }
        if (!correct) {
            --lives;
        }
    }

    bool charWasGuessed(char c) const { return guessedChars.count(c); }

   public:
    explicit Hangman(const std::string& word, int lives = 6)
        : targetWord(word), currentWord(word.size(), '_'), lives(lives) {}

    void play() {
        while (lives >= 0 && currentWord != targetWord) {
            std::cout << "\n\n\n" << HANGMAN_PICS[6 - lives] << "\n";
            std::cout << "\nWord: " << currentWord << "\n";
            std::cout << "Guessed: ";
            for (char c : guessedChars) std::cout << c << " ";
            std::cout << "\nLives left: " << lives << "\n";

            std::cout << "Enter a letter: ";
            char guess;
            std::cin >> guess;
            guess = std::tolower(guess);

            if (charWasGuessed(guess)) {
                std::cout << "You already guessed this letter\n";
                continue;
            }
            guessedChars.insert(guess);
            update(guess);
        }

        if (currentWord == targetWord) {
            std::cout << "\nYou guessed! The word was: " << targetWord << "\n";
        } else {
            std::cout << "\nYou died! The word was: " << targetWord << "\n";
        }
    }
};

int main() {
    std::string word;
    std::cout << "Enter a word to guess (no spaces, lowercase only): ";
    std::cin >> word;

    Hangman game(word);
    game.play();

    return 0;
}
