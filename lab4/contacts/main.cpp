#include <algorithm>
#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Contact {
   private:
    std::string m_name;
    std::string m_phone;
    std::string m_email;
    std::chrono::system_clock::time_point m_created;

   public:
    Contact(std::string name, std::string phone, std::string email, auto created)
        : m_name(std::move(name)),
          m_phone(std::move(phone)),
          m_email(std::move(email)),
          m_created(created) {}

    Contact(std::string name, std::string phone, std::string email)
        : m_name(std::move(name)),
          m_phone(std::move(phone)),
          m_email(std::move(email)),
          m_created(std::chrono::system_clock::now()) {}

    [[nodiscard]] std::string getName() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }

    [[nodiscard]] std::string getPhone() const { return m_phone; }
    void setPhone(const std::string& phone) { m_phone = phone; }

    [[nodiscard]] std::string getEmail() const { return m_email; }
    void setEmail(const std::string& email) { m_email = email; }

    [[nodiscard]] auto getCreated() const { return m_created; }
    void setCreated(auto created) { m_created = created; }

    [[nodiscard]] std::string toCSV() const {
        auto created_sec =
            std::chrono::duration_cast<std::chrono::seconds>(m_created.time_since_epoch()).count();
        return m_name + "," + m_phone + "," + m_email + "," + std::to_string(created_sec);
    }

    static Contact fromCSV(const std::string& csv) {
        std::istringstream ss(csv);
        std::string name, phone, email, created_str;

        std::getline(ss, name, ',');
        std::getline(ss, phone, ',');
        std::getline(ss, email, ',');
        std::getline(ss, created_str);

        auto created_sec = std::stoll(created_str);
        std::chrono::system_clock::time_point created =
            std::chrono::system_clock::time_point(std::chrono::seconds(created_sec));

        return {name, phone, email, created};
    }

    bool operator==(const Contact& other) const { return m_name == other.m_name; }
};

static void saveContactsToFile(const std::vector<Contact>& contacts, const std::string& filepath) {
    std::ofstream file(filepath);

    if (file.is_open()) {
        for (const Contact& contact : contacts) {
            file << contact.toCSV() << '\n';
        }
        file.close();
    } else {
        std::cerr << "Failed to open the storage file!\n";
    }
}

static std::vector<Contact> loadContactsFromFile(const std::string& filepath) {
    std::vector<Contact> contacts;

    std::ifstream file(filepath);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            contacts.emplace_back(Contact::fromCSV(line));
        }
        file.close();
    } else {
        std::cerr << "Failed to open the storage file!\n";
    }
    return contacts;
}

static void addContact(const Contact& contact, std::vector<Contact>& contacts,
                       const std::string& filepath) {
    contacts.emplace_back(contact);
    saveContactsToFile(contacts, filepath);
}

static void removeContact(const Contact& contact, std::vector<Contact>& contacts,
                          const std::string& filepath) {
    auto it = std::ranges::find(contacts, contact);
    if (it != contacts.end()) {
        contacts.erase(it);
        saveContactsToFile(contacts, filepath);
    } else {
        std::cout << "Contact not found.\n";
    }
}

static std::vector<Contact> searchContacts(const std::string& name,
                                           const std::vector<Contact>& contacts) {
    std::vector<Contact> results;
    for (const auto& contact : contacts) {
        if (contact.getName() == name) {
            results.emplace_back(contact);
        }
    }
    return results;
}

static void displayContacts(const std::vector<Contact>& contacts) {
    if (contacts.empty()) {
        std::cout << "No contacts available.\n";
        return;
    }
    std::cout << "======== Contact List ========\n";
    for (const auto& contact : contacts) {
        std::time_t created = std::chrono::system_clock::to_time_t(contact.getCreated());
        std::cout << "Name: " << contact.getName() << "\n"
                  << "Phone: " << contact.getPhone() << "\n"
                  << "Email: " << contact.getEmail() << "\n"
                  << "Created: " << std::put_time(std::localtime(&created), "%Y-%m-%d %H:%M:%S")
                  << "\n-----------------------------------\n";
    }
}

int main(int argc, char* argv[]) {
    std::filesystem::path storagePath =
        std::filesystem::canonical(argv[0]).parent_path() / "storage";
    std::filesystem::create_directories(storagePath);
    std::string contactsStorage = storagePath.string() + "/contacts.csv";

    std::vector<Contact> contacts = loadContactsFromFile(contactsStorage);

    if (contacts.empty()) {
        addContact({"John Doe", "555-1234", "john@example.com"}, contacts, contactsStorage);
        addContact({"Jane Smith", "555-5678", "jane@example.com"}, contacts, contactsStorage);
    }

    int choice = 0;
    do {
        std::cout << "\nContact Management System\n";
        std::cout << "1. Add Contact\n";
        std::cout << "2. Remove Contact\n";
        std::cout << "3. Search Contacts\n";
        std::cout << "4. Display All Contacts\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::string name, phone, email;
                std::cout << "Enter name: ";
                std::getline(std::cin, name);
                std::cout << "Enter phone: ";
                std::getline(std::cin, phone);
                std::cout << "Enter email: ";
                std::getline(std::cin, email);
                addContact(Contact(name, phone, email), contacts, contactsStorage);
                break;
            }
            case 2: {
                std::string name;
                std::cout << "Enter name to remove: ";
                std::getline(std::cin, name);
                removeContact(Contact(name, "", ""), contacts, contactsStorage);
                break;
            }
            case 3: {
                std::string name;
                std::cout << "Enter name to search: ";
                std::getline(std::cin, name);
                std::vector<Contact> results = searchContacts(name, contacts);
                displayContacts(results);
                break;
            }
            case 4:
                displayContacts(contacts);
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}