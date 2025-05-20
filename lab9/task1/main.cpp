#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

enum class Interval {
    MONTH = 12,
    QUATER = 4,
    YEAR = 1
};  // possible intervals and their number of "compounding" periods a year

class MortgageCalculator {
   private:
    double m_loan;
    double m_annualInterest;
    int m_term;
    Interval m_interval;

    [[nodiscard]] int periodsInAYear() const { return static_cast<int>(m_interval); }

   public:
    MortgageCalculator(double loan, double annualInterest, int term, Interval interval)
        : m_loan(loan), m_annualInterest(annualInterest), m_term(term), m_interval(interval) {}
    [[nodiscard]] double periodPayment() const {
        int m = periodsInAYear();
        double rate = (m_annualInterest / 100.0) / m;  // interest rate in a period
        int n = m_term * m;                            // number of payments

        if (rate == 0.0) return m_loan / n;
        double p = std::pow(1 + rate, n);
        return m_loan * rate * p / (p - 1);
    }
    [[nodiscard]] double totalPaid() const { return periodPayment() * m_term * periodsInAYear(); }

    [[nodiscard]] double totalInterest() const { return totalPaid() - m_loan; }
};

int main() {
    double loan, rate;
    int term, choice;

    std::cout << "Enter loan amount: ";
    std::cin >> loan;

    std::cout << "Enter annual interest rate (%): ";
    std::cin >> rate;

    std::cout << "Loan term in years: ";
    std::cin >> term;

    std::cout
        << "Select the compounding interval:\n1) Month\n2) Quarter\n3) Year\nEnter the number?: ";
    std::cin >> choice;

    Interval interval;
    switch (choice) {
        case 1:
            interval = Interval::MONTH;
            break;
        case 2:
            interval = Interval::QUATER;
            break;
        case 3:
            interval = Interval::YEAR;
            break;
        default:
            throw("Invalid interval");
    }

    MortgageCalculator calculator(loan, rate, term, interval);

    double payment = calculator.periodPayment();
    double interest = calculator.totalInterest();

    std::cout << std::fixed << std::setprecision(2) << "\nPeriodic payment: $" << payment
              << "\nTotal interest: $" << interest << "\n";

    return 0;
}
