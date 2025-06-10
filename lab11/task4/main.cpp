#include <iostream>
#include <string>
#include <unordered_map>

class Product {
    int m_id;
    std::string m_name;
    int m_quantity;

   public:
    Product(int id, std::string name, int quantity)
        : m_id(id), m_name(std::move(name)), m_quantity(quantity) {}

    int getId() const { return m_id; }
    const std::string& getName() const { return m_name; }
    int getQuantity() const { return m_quantity; }

    void purchase(int amount) {
        if (amount <= 0) {
            std::cerr << "Purchase amount must be positive\n";
            return;
        }
        m_quantity += amount;
    }

    bool sell(int amount) {
        if (amount <= 0) {
            std::cerr << "Sale amount must be positive\n";
            return false;
        }
        if (amount > m_quantity) {
            std::cerr << "Not enough stock\n";
            return false;
        }
        m_quantity -= amount;
        return true;
    }
};

class StockSystem {
    std::unordered_map<int, Product> inventory;

   public:
    void addProduct(int id, const std::string& name, int quantity) {
        if (inventory.contains(id)) {
            std::cerr << "Product ID already exists\n";
            return;
        }
        inventory.emplace(id, Product(id, name, quantity));
        std::cout << "Product added\n";
    }

    void purchase(int id, int amount) {
        auto it = inventory.find(id);
        if (it != inventory.end()) {
            it->second.purchase(amount);
        } else {
            std::cerr << "Product not found\n";
        }
    }

    void sell(int id, int amount) {
        auto it = inventory.find(id);
        if (it != inventory.end()) {
            it->second.sell(amount);
        } else {
            std::cerr << "Product not found\n";
        }
    }

    void printProduct(int id) const {
        auto it = inventory.find(id);
        if (it != inventory.end()) {
            const Product& p = it->second;
            std::cout << "ID: " << p.getId() << ", Name: " << p.getName()
                      << ", Quantity: " << p.getQuantity() << '\n';
        } else {
            std::cerr << "Product not found\n";
        }
    }
};

int main() {
    StockSystem system;
    std::string command;

    std::cout << "Stock started!\n\nCommands: add, purchase, sell, print, exit\n\n"
                 "Example:\n"
                 "add 1 Apples 50\n"
                 "purchase 1 20\n"
                 "sell 1 10\n"
                 "print 1\n\n";

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "add") {
            int id, qty;
            std::string name;
            std::cin >> id >> name >> qty;
            system.addProduct(id, name, qty);
        } else if (command == "purchase") {
            int id, qty;
            std::cin >> id >> qty;
            system.purchase(id, qty);
        } else if (command == "sell") {
            int id, qty;
            std::cin >> id >> qty;
            system.sell(id, qty);
        } else if (command == "print") {
            int id;
            std::cin >> id;
            system.printProduct(id);
        } else if (command == "exit") {
            break;
        } else {
            std::cerr << "Unknown command\n";
        }
    }

    return 0;
}
