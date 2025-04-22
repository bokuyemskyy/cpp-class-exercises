#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Product {
    int id;
    std::string name;
    float price;
    int quantity;
};

static void displayInventory(const std::vector<Product>& inventory) {
    std::cout << std::left << std::setw(5) << "ID" << std::setw(15) << "Name" << std::setw(10)
              << "Price" << std::setw(10) << "Quantity" << "\n";
    for (auto const& product : inventory) {
        std::cout << std::left << std::setw(5) << product.id << std::setw(15) << product.name
                  << std::setw(10) << product.price << std::setw(10) << product.quantity << "\n";
    }
    std::cout << "\n";
}

static void addProduct(std::vector<Product>& inventory, const Product& newProduct) {
    inventory.emplace_back(newProduct);
}

static void removeProduct(std::vector<Product>& inventory, int id) {
    for (auto it = inventory.begin(); it != inventory.end(); it++) {
        if (it->id == id) {
            inventory.erase(it);
        }
    }
}

int main() {
    std::vector<Product> inventory = {{.id = 1, .name = "Keyboard", .price = 49.99, .quantity = 10},
                                      {.id = 2, .name = "Mouse", .price = 25.50, .quantity = 25},
                                      {.id = 3, .name = "Monitor", .price = 199.99, .quantity = 5}};

    displayInventory(inventory);

    std::cout << "\nAdding new product\n";
    addProduct(inventory, {.id = 4, .name = "Headphones", .price = 89.99, .quantity = 8});
    displayInventory(inventory);

    std::cout << "\nRemoving product with id = 2\n";
    removeProduct(inventory, 2);
    displayInventory(inventory);
}