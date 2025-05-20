#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Cipherer {
    const std::string key = "key12311!?";

   public:
    std::string encrypt(const std::string& data) {
        std::string result = data;
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] ^ key[i % key.size()];
        }
        return result;
    }

    std::string decrypt(const std::string& data) { return encrypt(data); }
};

class Entry {
   public:
    std::string app;
    std::string username;
    std::string password;

    Entry(std::string app, std::string username, std::string password)
        : app(std::move(app)), username(std::move(username)), password(std::move(password)) {}
};

class PasswordManager {
    std::string master_username;
    std::string master_password;
    bool authenticated = false;

    std::vector<Entry> entries;
    Cipherer cipherer;
    const std::string data_file = "passwords.data";

   public:
    PasswordManager(std::string username, std::string password)
        : master_username(std::move(username)), master_password(std::move(password)) {}

    bool authenticate(const std::string& username, const std::string& password) {
        authenticated = (username == master_username && password == master_password);
        if (authenticated) load();
        return authenticated;
    }

    void add(const std::string& app, const std::string& username, const std::string& password) {
        if (!authenticated) {
            std::cout << "Not authenticated\n";
            return;
        }
        entries.emplace_back(app, username, password);
        save();
    }

    void edit(size_t index, const std::string& app, const std::string& username,
              const std::string& password) {
        if (!authenticated) {
            std::cout << "Not authenticated\n";
            return;
        }
        if (index >= entries.size()) {
            std::cout << "Index out of bounds\n";
            return;
        }
        entries[index] = Entry(app, username, password);
        save();
    }

    void remove(size_t index) {
        if (!authenticated) {
            std::cout << "Not authenticated\n";
            return;
        }
        if (index >= entries.size()) {
            std::cout << "Invalid index\n";
            return;
        }
        entries.erase(entries.begin() + index);
        save();
    }

    void list() const {
        if (!authenticated) {
            std::cout << "Not authenticated\n";
            return;
        }
        for (size_t i = 0; i < entries.size(); ++i) {
            std::cout << i << ": " << entries[i].app << " | " << entries[i].username << " | "
                      << entries[i].password << "\n";
        }
    }

   private:
    void load() {
        entries.clear();
        std::ifstream file(data_file, std::ios::binary);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string app, username, encrypted_password;

            if (!std::getline(iss, app, '|')) continue;
            if (!std::getline(iss, username, '|')) continue;
            if (!std::getline(iss, encrypted_password)) continue;

            std::string decrypted_password = cipherer.decrypt(encrypted_password);
            entries.emplace_back(app, username, decrypted_password);
        }
    }

    void save() {
        std::ofstream file(data_file, std::ios::binary | std::ios::trunc);
        for (const auto& c : entries) {
            std::string encrypted_password = cipherer.encrypt(c.password);
            file << c.app << "|" << c.username << "|" << encrypted_password << "\n";
        }
    }
};

int main() {
    PasswordManager pm("admin", "admin");

    std::cout << "(hint: for showcase, the credentials are user: 'admin' and pass: 'admin'): ";

    std::string user, pass;
    std::cout << "Enter username: ";
    std::cin >> user;
    std::cout << "Enter password: ";
    std::cin >> pass;

    if (!pm.authenticate(user, pass)) {
        std::cout << "Authentication failed.\n";
        return 1;
    }

    int choice;
    while (true) {
        std::cout << "Choose the action:\n1. Add entry\n2. Edit entry\n3. Remove entry\n4. List "
                     "\n5. Exit\n";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
            case 1: {
                std::string app, username, password;
                std::cout << "Enter app: ";
                std::getline(std::cin, app);
                std::cout << "Enter username: ";
                std::getline(std::cin, username);
                std::cout << "Enter password: ";
                std::getline(std::cin, password);
                pm.add(app, username, password);
                pm.list();
                break;
            }
            case 2: {
                size_t index;
                std::string app, username, password;
                std::cout << "Enter entry index: ";
                std::cin >> index;
                std::cout << "Enter new app: ";
                std::getline(std::cin, app);
                std::cout << "Enter new username: ";
                std::getline(std::cin, username);
                std::cout << "Enter new password: ";
                std::getline(std::cin, password);
                pm.edit(index, app, username, password);
                pm.list();
                break;
            }
            case 3: {
                size_t index;
                std::cout << "Enter entry index: ";
                std::cin >> index;
                pm.remove(index);
                pm.list();
                break;
            }
            case 4:
                pm.list();
                break;
            case 5:
                return 0;
            default:
                std::cout << "Invalid choice\n";
                break;
        }
    }

    return 0;
}
