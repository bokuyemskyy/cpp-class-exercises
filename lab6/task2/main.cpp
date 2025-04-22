#include <cassert>
#include <iostream>
#include <string>
#include <utility>

class Account {
   private:
    int m_id;
    std::string m_holder;
    float m_balance;

   public:
    Account(int id, std::string holder, float balance)
        : m_id(id), m_holder(std::move(holder)), m_balance(balance) {};

    [[nodiscard]] int getId() const { return m_id; }
    [[nodiscard]] std::string getHolder() const { return m_holder; }

    float deposit(float amount) {
        if (amount > 0) {
            m_balance += amount;
        } else {
            std::cerr << "Deposit amount should be positive!\n";
        }
        return m_balance;
    }
    float withdraw(float amount) {
        if (amount > 0) {
            if (m_balance - amount >= 0) {
                m_balance -= amount;
            } else {
                std::cerr << "Balance cant be negative!\n";
            }
        } else {
            std::cerr << "Withdraw amount should be positive!\n";
        }
        return m_balance;
    }

    [[nodiscard]] float getBalance() const { return m_balance; }
};

int main() {
    Account acc(123, "John", 1000.0);

    std::cout << "Account ID: " << acc.getId() << '\n';
    std::cout << "Account Holder: " << acc.getHolder() << '\n';
    std::cout << "Account Balance: " << acc.getBalance() << '\n';

    acc.deposit(200.0);
    std::cout << "Account Balance after deposit: " << acc.getBalance() << '\n';
    acc.withdraw(50.0);
    std::cout << "Account Balance after withdraw: " << acc.getBalance() << '\n';

    return 0;
}
