#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <variant>
#include <vector>

class Contact {
   public:
    enum class Type { Personal, Business };

    struct PersonalInfo {
        std::string name;
        std::string phone;
        std::string email;
    };

    struct BusinessInfo {
        std::string company;
        std::string phone;
        std::string email;
        std::string position;
    };

    using Info = std::variant<PersonalInfo, BusinessInfo>;

    Contact(std::string name, std::string phone, std::string email, Type type)
        : m_name(std::move(name)),
          m_phone(std::move(phone)),
          m_email(std::move(email)),
          m_type(type) {}

    [[nodiscard]] const std::string& getName() const { return m_name; }
    [[nodiscard]] const std::string& getPhone() const { return m_phone; }
    [[nodiscard]] const std::string& getEmail() const { return m_email; }
    [[nodiscard]] Type getType() const { return m_type; }

    void display() const {
        std::cout << "Name: " << m_name << "\nPhone: " << m_phone << "\nEmail: " << m_email
                  << std::endl;
        (m_type == Type::Business) ? std::cout << "Type: Business\n"
                                   : std::cout << "Type: Personal\n";
    }

   private:
    std::string m_name;
    std::string m_phone;
    std::string m_email;
    Type m_type;
};

class Book {
   public:
    void add(const Contact& contact) { m_contacts.push_back(contact); }

    void remove(const std::string& name) {
        m_contacts.erase(
            std::remove_if(m_contacts.begin(), m_contacts.end(),
                           [&name](const Contact& contact) { return contact.getName() == name; }),
            m_contacts.end());
    }

    std::optional<Contact> search(const std::string& name) {
        for (const auto& contact : m_contacts) {
            if (contact.getName() == name) {
                return contact;
            }
        }
        return std::nullopt;
    }

    void display() {
        for (const auto& contact : m_contacts) {
            contact.display();
            std::cout << "-----------------\n";
        }
    }

   private:
    std::vector<Contact> m_contacts;
};

int main() {
    Book book;

    book.add(Contact("Saul", "123456", "tun@email.com", Contact::Type::Personal));
    book.add(Contact("Goodman", "987654", "tun@agh.edu.pl", Contact::Type::Business));

    std::cout << "Contacts:\n";
    book.display();

    auto contact = book.search("Saul");
    if (contact) {
        std::cout << "Found:\n";
        contact->display();
    } else {
        std::cout << "Not found\n";
    }

    book.remove("Goodman");

    std::cout << "Contacts after removal:\n";
    book.display();

    return 0;
}
