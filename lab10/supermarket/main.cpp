#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

class Product {
    std::string m_name;
    double m_price;
    int m_quantity;

   public:
    Product(std::string n, double p, int q) : m_name(std::move(n)), m_price(p), m_quantity(q) {}

    [[nodiscard]] double getTotal() const { return m_price * m_quantity; }

    void print(std::ostream& out) const {
        out << std::setw(15) << m_name << std::setw(15) << m_price << std::setw(15) << m_quantity
            << std::setw(15) << getTotal() << "\n";
    }
};

class Invoice {
    std::vector<Product> m_products;
    double m_discount = 0.0;

   public:
    void addItem(const std::string& name, double price, int quantity) {
        m_products.emplace_back(name, price, quantity);
    }

    void applyDiscount(double percent) { m_discount = percent; }

    double computeTotal() const {
        double total = 0;
        for (const auto& item : m_products) total += item.getTotal();
        return total * (1 - m_discount / 100.0);
    }

    void printInvoice(std::ostream& out) const {
        out << std::setw(15) << "Product" << std::setw(15) << "Price" << std::setw(15) << "Quantity"
            << std::setw(15) << "Total\n";

        out << std::string(60, '-') << "\n";

        for (const auto& item : m_products) item.print(out);

        out << std::string(60, '-') << "\n";

        out << "Discount: " << m_discount << "%\n";
        out << "So the final total is: $" << computeTotal() << "\n";
    }
};

class BillingSystem {
    Invoice m_invoice;

   public:
    void scanItems() {
        while (true) {
            std::string name;
            double price;
            int quantity;

            std::cout << "Enter item name (or 'done'): ";
            std::cin >> name;

            if (name == "done") break;

            std::cout << "Price: ";
            std::cin >> price;
            std::cout << "Quantity: ";
            std::cin >> quantity;

            m_invoice.addItem(name, price, quantity);
        }
    }

    void handleDiscount() {
        double percent;
        std::cout << "Enter discount % (0 if none): ";
        std::cin >> percent;

        m_invoice.applyDiscount(percent);
    }

    void selectPayment() {
        int option;
        std::cout << "Select payment meth.:\n1. Cash\n2. Card\nChoice: ";
        std::cin >> option;
    }

    void generateBill() { m_invoice.printInvoice(std::cout); }

    void run() {
        scanItems();
        handleDiscount();
        selectPayment();
        generateBill();
    }
};

int main() {
    BillingSystem system;
    system.run();
}
