#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Book {
    int m_id;
    std::string m_title;
    int m_totalCopies;
    int m_availableCopies;

    struct Record {
        std::string member;
        int issueDay;
        bool returned = false;
    };

    std::vector<Record> history;

   public:
    Book(int id, std::string title, int copies)
        : m_id(id), m_title(std::move(title)), m_totalCopies(copies), m_availableCopies(copies) {}

    int getId() const { return m_id; }
    const std::string& getTitle() const { return m_title; }
    int getAvailable() const { return m_availableCopies; }

    bool issue(const std::string& member, int day) {
        if (m_availableCopies <= 0) {
            std::cerr << "No copies available\n";
            return false;
        }
        m_availableCopies--;
        history.push_back({member, day});
        return true;
    }

    bool returnBook(const std::string& member, int day) {
        for (auto& rec : history) {
            if (!rec.returned && rec.member == member) {
                rec.returned = true;
                m_availableCopies++;
                return true;
            }
        }
        std::cerr << "No active loan found for " << member << "\n";
        return false;
    }

    void reportOverdue(int currentDay) const {
        for (const auto& rec : history) {
            if (!rec.returned && currentDay - rec.issueDay > 14) {
                std::cout << "Overdue: Book '" << m_title << "' | Member: " << rec.member
                          << " | Day issued: " << rec.issueDay << '\n';
            }
        }
    }

    void print() const {
        std::cout << "ID: " << m_id << ", Title: " << m_title
                  << ", Available: " << m_availableCopies << ", Total: " << m_totalCopies << '\n';
    }
};

class Library {
    std::unordered_map<int, Book> books;

   public:
    void addBook(int id, const std::string& title, int copies) {
        if (books.contains(id)) {
            std::cerr << "Book ID already exists\n";
            return;
        }
        books.emplace(id, Book(id, title, copies));
        std::cout << "Book added\n";
    }

    void issueBook(int id, const std::string& member, int day) {
        auto it = books.find(id);
        if (it != books.end()) {
            it->second.issue(member, day);
        } else {
            std::cerr << "Book not found\n";
        }
    }

    void returnBook(int id, const std::string& member, int day) {
        auto it = books.find(id);
        if (it != books.end()) {
            it->second.returnBook(member, day);
        } else {
            std::cerr << "Book not found\n";
        }
    }

    void reportOverdue(int currentDay) const {
        for (const auto& [id, book] : books) {
            book.reportOverdue(currentDay);
        }
    }

    void printBook(int id) const {
        auto it = books.find(id);
        if (it != books.end()) {
            it->second.print();
        } else {
            std::cerr << "Book not found\n";
        }
    }
};

int main() {
    Library lib;
    std::string command;

    std::cout << "Library started!\n\nCommands: add, issue, return, report, print, exit\n\n"
                 "Example:\n"
                 "add 1 Dune 3\n"
                 "issue 1 Alice 5\n"
                 "return 1 Alice 20\n"
                 "report 25\n"
                 "print 1\n\n";

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "add") {
            int id, copies;
            std::string title;
            std::cin >> id >> title >> copies;
            lib.addBook(id, title, copies);
        } else if (command == "issue") {
            int id, day;
            std::string member;
            std::cin >> id >> member >> day;
            lib.issueBook(id, member, day);
        } else if (command == "return") {
            int id, day;
            std::string member;
            std::cin >> id >> member >> day;
            lib.returnBook(id, member, day);
        } else if (command == "report") {
            int day;
            std::cin >> day;
            lib.reportOverdue(day);
        } else if (command == "print") {
            int id;
            std::cin >> id;
            lib.printBook(id);
        } else if (command == "exit") {
            break;
        } else {
            std::cerr << "Unknown command\n";
        }
    }

    return 0;
}
