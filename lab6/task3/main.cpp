#include <cassert>
#include <iostream>
#include <string>
#include <utility>

class Employee {
   private:
    int m_id;
    std::string m_name;
    float m_salary;

    static int s_totalEmployees;
    static float s_totalSalary;

   public:
    Employee(int id, std::string name, float salary)
        : m_id(id), m_name(std::move(name)), m_salary(salary) {
        s_totalEmployees++;
        s_totalSalary += salary;
    }

    ~Employee() {
        s_totalEmployees--;
        updateSalary(0);
    }

    void updateSalary(float newSalary) {
        if (newSalary >= 0.0F) {
            s_totalSalary -= m_salary;
            m_salary = newSalary;
            s_totalSalary += m_salary;
        } else {
            std::cerr << "Salary cannot be negative!\n";
        }
    }

    void display() const {
        std::cout << "ID: " << m_id << ", Name: " << m_name << ", Salary: " << m_salary << '\n';
    }

    [[nodiscard]] int getId() const { return m_id; }
    [[nodiscard]] std::string getName() const { return m_name; }
    [[nodiscard]] float getSalary() const { return m_salary; }

    static void showStats() {
        std::cout << "Total Employees: " << s_totalEmployees << '\n';
        std::cout << "Total Salary Paid: " << s_totalSalary << '\n';
    }
};

int Employee::s_totalEmployees = 0;
float Employee::s_totalSalary = 0.0F;

int main() {
    Employee e1(1, "Ivan", 1456);
    Employee e2(2, "Andrew", 1034);

    e1.display();
    e2.display();
    Employee::showStats();

    e1.updateSalary(3500.0f);
    e1.display();
    Employee::showStats();

    return 0;
}
