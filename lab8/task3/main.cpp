#include <cstdlib>
#include <ctime>
#include <iostream>

class Casino {
   private:
    int m_balance;
    int m_bet{};
    int m_minNumber, m_maxNumber;

   public:
    Casino(int startBalance, int minNumber = 1, int maxNumber = 10)
        : m_balance(startBalance), m_minNumber(minNumber), m_maxNumber(maxNumber) {
        srand(time(0));
    }

    void play() {
        while (m_balance > 0) {
            std::cout << "Your balance is: $" << m_balance << "\nEnter your bet! : $";
            std::cin >> m_bet;
            if (m_bet <= 0 || m_bet > m_balance) {
                std::cout << "Invalid bet!\n";
                continue;
            }

            int guess;
            int number = (rand() % (m_maxNumber - m_minNumber + 1)) + m_minNumber;
            std::cout << "Give your guess: ";
            std::cin >> guess;

            if (guess == number) {
                std::cout << "Yes! You won $" << m_bet * (m_maxNumber - m_minNumber - 2) << ".\n";
                m_balance += m_bet * (m_maxNumber - m_minNumber - 2);
            } else {
                std::cout << "No! The number was " << number << ". You lose $" << m_bet << ".\n";
                m_balance -= m_bet;
            }

            if (m_balance <= 0) {
                std::cout << "Out of money! Game over.\n";
                break;
            }

            std::cout << "Start the game again? (y/n): ";
            char choice;
            std::cin >> choice;
            if (choice == 'n') break;
        }
    }
};

int main() {
    int initialBalance;
    std::cout << "Your initial balance will be? $";
    std::cin >> initialBalance;
    Casino game(initialBalance);
    game.play();
    return 0;
}