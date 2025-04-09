#include <iostream>

int main() {
    int amount;
    int coins[] = {50, 20, 10, 5, 2, 1};
    int numCoins[6] = {0};

    std::cout << "Enter amount in grosze (1-999): ";
    std::cin >> amount;
    if (amount <= 0 || amount >= 1000) {
        std::cout << "Invalid amount, enter a value between 1 and 999 grosze." << std::endl;
        return 1;
    }

    int remaining = amount;
    for (int i = 0; i < 6; i++) {
        numCoins[i] = remaining / coins[i];
        remaining = remaining % coins[i];
    }

    std::cout << "\nChange as " << amount << " grosze:" << std::endl;
    for (int i = 0; i < 6; i++) {
        if (numCoins[i] > 0) {
            std::cout << numCoins[i] << " times - " << coins[i] << " grosze coin" << std::endl;
        }
    }

    return 0;
}