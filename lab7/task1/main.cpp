#include <iostream>
#include <string>

class Product {
   private:
    int m_id;
    std::string m_name;
    float m_price;
    int m_quantity;

    static int s_totalProducts;
    static float s_totalPrice;

   public:
    Product(int id, const std::string& name, float price, int quantity)
        : m_id(id), m_name(name), m_price(price), m_quantity(quantity) {
        s_totalProducts++;
        s_totalPrice += m_price * m_quantity;
    }
    ~Product() {
        s_totalProducts--;
        s_totalPrice -= m_price * m_quantity;
    }
    void addProduct(int q) {
        m_quantity += q;
        s_totalPrice += m_price * q;
    }
    void removeProduct(int q) {
        if (q > m_quantity) {
            std::cout << "Not enough quantity to remove.\n";
            return;
        }
        m_quantity -= q;
        s_totalPrice -= m_price * q;
    }
    void display() const {
        std::cout << "ID: " << m_id << std::endl;
        std::cout << "Name: " << m_name << std::endl;
        std::cout << "Price: $" << m_price << std::endl;
        std::cout << "Quantity: " << m_quantity << std::endl;
    }
    static void displayTotal() {
        std::cout << "Total products: " << s_totalProducts << std::endl;
        std::cout << "Total price: $" << s_totalPrice << std::endl;
    }
};

int Product::s_totalProducts = 0;
float Product::s_totalPrice = 0.0;

int main() {
    Product p1(101, "Keyboard", 2.0, 10);
    Product p2(102, "Mouse", 1.0, 15);

    p1.display();
    p2.display();
    Product::displayTotal();

    p1.addProduct(5);
    p2.removeProduct(10);

    Product::displayTotal();

    return 0;
}