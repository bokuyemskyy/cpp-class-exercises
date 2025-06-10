#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

class Account {
   private:
    int m_id;
    std::string m_holder;
    float m_balance;

   public:
    Account(int id, std::string holder, float balance)
        : m_id(id), m_holder(std::move(holder)), m_balance(balance) {}

    int getId() const { return m_id; }
    const std::string& getHolder() const { return m_holder; }
    float getBalance() const { return m_balance; }

    void deposit(float amount) {
        if (amount <= 0) {
            std::cerr << "Deposit must be positive\n";
            return;
        }
        m_balance += amount;
    }

    bool withdraw(float amount) {
        if (amount <= 0) {
            std::cerr << "Withdrawal must be positive\n";
            return false;
        }
        if (amount > m_balance) {
            std::cerr << "No such funds\n";
            return false;
        }
        m_balance -= amount;
        return true;
    }
};

class BankingSystem {
   private:
    std::unordered_map<int, Account> accounts;

   public:
    void createAccount(int id, const std::string& holder, float initialBalance) {
        if (accounts.contains(id)) {
            std::cerr << "Account ID already exists\n";
            return;
        }
        accounts.emplace(id, Account(id, holder, initialBalance));
    }

    void deposit(int id, float amount) {
        auto it = accounts.find(id);
        if (it != accounts.end()) {
            it->second.deposit(amount);
        } else {
            std::cerr << "Account not found\n";
        }
    }

    void withdraw(int id, float amount) {
        auto it = accounts.find(id);
        if (it != accounts.end()) {
            it->second.withdraw(amount);
        } else {
            std::cerr << "Account not found\n";
        }
    }

    void transfer(int fromId, int toId, float amount) {
        auto fromIt = accounts.find(fromId);
        auto toIt = accounts.find(toId);
        if (fromIt == accounts.end() || toIt == accounts.end()) {
            std::cerr << "One or both accounts not found\n";
            return;
        }
        if (fromIt->second.withdraw(amount)) {
            toIt->second.deposit(amount);
        }
    }

    void printAccount(int id) const {
        auto it = accounts.find(id);
        if (it != accounts.end()) {
            const Account& acc = it->second;
            std::cout << "ID: " << acc.getId() << ", Holder: " << acc.getHolder()
                      << ", Balance: " << acc.getBalance() << '\n';
        } else {
            std::cerr << "Account not found\n";
        }
    }
};

int main() {
    BankingSystem bank;
    std::string command;

    std::cout << "Bank started!\n\nCommands: create, deposit, withdraw, transfer, print, "
                 "exit\n\nExample: create "
                 "101 Alice 500\ndeposit 101 200\ncreate 102 Bob 300\ntransfer 101 102 100\nprint "
                 "101\nprint 102\n\n";

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "create") {
            int id;
            std::string name;
            float balance;
            std::cin >> id >> name >> balance;
            bank.createAccount(id, name, balance);
        } else if (command == "deposit") {
            int id;
            float amount;
            std::cin >> id >> amount;
            bank.deposit(id, amount);
        } else if (command == "withdraw") {
            int id;
            float amount;
            std::cin >> id >> amount;
            bank.withdraw(id, amount);
        } else if (command == "transfer") {
            int fromId, toId;
            float amount;
            std::cin >> fromId >> toId >> amount;
            bank.transfer(fromId, toId, amount);
        } else if (command == "print") {
            int id;
            std::cin >> id;
            bank.printAccount(id);
        } else if (command == "exit") {
            break;
        } else {
            std::cerr << "Unknown command\n";
        }
    }

    return 0;
}
