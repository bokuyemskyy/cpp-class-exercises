#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Student {
   private:
    std::string m_name;
    int m_id;
    std::map<std::string, double> m_grades;
    std::string m_comment;

   public:
    Student(std::string n, int i) : m_name(std::move(n)), m_id(i) {}
    ~Student() {}

    void addGrade(const std::string& subject, double grade) { m_grades[subject] = grade; }
    void setComment(const std::string& c) { m_comment = c; }
    void editName(const std::string& newName) { m_name = newName; }

    [[nodiscard]] int getId() const { return m_id; }

    void printReport(std::ostream& out) const {
        out << "Name: " << m_name << "\nID: " << m_id << "\nGrades:\n";
        for (const auto& [subj, grade] : m_grades) out << subj << ": " << grade << "\n";
        out << "Comment: " << m_comment << "\n";
    }
};

class ManagementSystem {
   private:
    std::vector<std::unique_ptr<Student>> m_students;

   public:
    void addStudent() {
        std::string name;
        int id;
        std::cout << "Enter name: ";
        std::cin >> name;
        std::cout << "Enter id: ";
        std::cin >> id;
        m_students.push_back(std::make_unique<Student>(name, id));
    }

    Student* findStudent(int id) {
        for (auto& s : m_students)
            if (s->getId() == id) return s.get();
        return nullptr;
    }

    void addGrade() {
        int id;
        std::string subj;
        double grade;
        std::cout << "ID: ";
        std::cin >> id;
        Student* s = findStudent(id);
        if (!s) return;
        std::cout << "Subject: ";
        std::cin >> subj;
        std::cout << "Grade: ";
        std::cin >> grade;
        s->addGrade(subj, grade);
    }

    void editComment() {
        int id;

        std::string c;
        std::cout << "ID: ";
        std::cin >> id;
        Student* s = findStudent(id);

        if (!s) return;

        std::cout << "Comment: ";
        std::cin.ignore();
        std::getline(std::cin, c);
        s->setComment(c);
    }

    void printStudent() {
        int id;

        std::cout << "ID: ";
        std::cin >> id;
        Student* s = findStudent(id);

        if (!s) return;

        s->printReport(std::cout);
    }

    void saveToFile() {
        std::ofstream out("report.txt");

        for (const auto& s : m_students) {
            s->printReport(out);
            out << "-------\n";
        }
    }

    void menu() {
        int choice;
        do {
            std::cout
                << "\n\n\n1. Add student\n2. Add grade\n3. Edit comment\n4. Print report\n5. Save "
                   "to file\n6. Quit\nEnter your choice: ";
            std::cin >> choice;
            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    addGrade();
                    break;
                case 3:
                    editComment();
                    break;
                case 4:
                    printStudent();
                    break;
                case 5:
                    saveToFile();
                    break;
            }
        } while (choice != 6);
    }
};

int main() {
    ManagementSystem m;
    m.menu();
}
