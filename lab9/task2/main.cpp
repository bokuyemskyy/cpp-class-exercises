#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Product {
   private:
    std::string m_name;
    std::string m_category;
    double m_price;
    int m_quantity;

   public:
    Product(std::string name, std::string category, double price, int quantity)
        : m_name(std::move(name)),
          m_category(std::move(category)),
          m_price(price),
          m_quantity(quantity) {}

    [[nodiscard]] const std::string& getName() const { return m_name; }
    [[nodiscard]] const std::string& getCategory() const { return m_category; }
    [[nodiscard]] double getPrice() const { return m_price; }
    [[nodiscard]] int getQuantity() const { return m_quantity; }

    void setPrice(double price) { m_price = price; }
    void setQuantity(int quantity) { m_quantity = quantity; }

    void display() const {
        std::cout << std::left << std::setw(15) << m_name << std::setw(15) << m_category
                  << std::right << std::setw(15) << m_price << std::setw(15) << m_quantity << '\n';
    }
};

class Inventory {
   private:
    std::vector<Product> m_products;

   public:
    void addProduct(const Product& p) { m_products.push_back(p); }

    void removeProduct(const std::string& name) {
        auto it = std::remove_if(m_products.begin(), m_products.end(),
                                 [&](const Product& p) { return p.getName() == name; });
        if (it != m_products.end()) {
            m_products.erase(it, m_products.end());
            std::cout << "Product was removed\n";
        } else {
            std::cout << "Product was not found\n";
        }
    }

    void updateProduct(const std::string& name, double price, int quantity) {
        for (auto& p : m_products) {
            if (p.getName() == name) {
                p.setPrice(price);
                p.setQuantity(quantity);
                std::cout << "Product was updated\n";
                return;
            }
        }
        std::cout << "Product was not found\n";
    }

    void searchName(const std::string& name) const {
        bool found = false;
        for (const auto& p : m_products) {
            if (p.getName() == name) {
                p.display();
                found = true;
            }
        }
        if (!found) std::cout << "Product was not found\n";
    }

    void searchCategory(const std::string& category) const {
        bool found = false;
        for (const auto& p : m_products) {
            if (p.getCategory() == category) {
                p.display();
                found = true;
            }
        }
        if (!found) std::cout << "Category was not found\n";
    }

    void print() const {
        std::cout << std::left << std::setw(15) << "Name" << std::setw(15) << "Category"
                  << std::right << std::setw(15) << "Price" << std::setw(15) << "Quantity" << "\n";
        std::cout << std::string(50, '-') << '\n';
        for (const auto& p : m_products) {
            p.display();
        }
    }
};

int main() {
    Inventory store;
    int choice;

    while (true) {
        std::cout << "\nMenu:\n"
                  << "1. Add product\n"
                  << "2. Remove product\n"
                  << "3. Update product\n"
                  << "4. Search by name\n"
                  << "5. Search by category\n"
                  << "6. Print information\n"
                  << "7. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 7) break;

        std::string name, category;
        double price;
        int quantity;

        switch (choice) {
            case 1:
                std::cout << "Enter the name, category, price, quantity: ";
                std::cin >> name >> category;
                if (!(std::cin >> price >> quantity)) {
                    std::cerr << "Invalid input for price or quantity\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    store.addProduct(Product(name, category, price, quantity));
                }
                break;
            case 2:
                std::cout << "Enter product name to find and remove: ";
                std::cin >> name;
                store.removeProduct(name);
                break;
            case 3:
                std::cout << "Enter name, new price, new quantity: ";
                std::cin >> name;
                if (!(std::cin >> price >> quantity)) {
                    std::cerr << "Invalid input for price or quantity\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    store.updateProduct(name, price, quantity);
                }
                break;
            case 4:
                std::cout << "Enter product name: ";
                std::cin >> name;
                store.searchName(name);
                break;
            case 5:
                std::cout << "Enter category: ";
                std::cin >> category;
                store.searchCategory(category);
                break;
            case 6:
                store.print();
                break;
            default:
                std::cout << "Invalid choice\n";
        }
    }

    return 0;
}
