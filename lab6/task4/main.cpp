#include <cassert>
#include <iostream>
#include <numeric>

class Fraction {
   private:
    int m_numerator;
    int m_denominator;

    void simplify() {
        int gcd = std::gcd(m_numerator, m_denominator);
        if (gcd != 0) {
            m_numerator /= gcd;
            m_denominator /= gcd;
        }
        if (m_denominator < 0) {
            m_numerator *= -1;
            m_denominator *= -1;
        }
    }

   public:
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator(numerator), m_denominator(denominator) {
        if (denominator == 0) {
            std::cerr << "Denominator cant be zero!\n";
            std::exit(1);
        }
        simplify();
    }

    [[nodiscard]] int getNumerator() const { return m_numerator; }
    [[nodiscard]] int getDenominator() const { return m_denominator; }

    void display() const { std::cout << m_numerator << '/' << m_denominator << '\n'; }

    Fraction operator+(const Fraction& other) const {
        int num = (m_numerator * other.m_denominator) + (other.m_numerator * m_denominator);
        int den = m_denominator * other.m_denominator;
        return {num, den};
    }

    Fraction operator-(const Fraction& other) const {
        int num = (m_numerator * other.m_denominator) - (other.m_numerator * m_denominator);
        int den = m_denominator * other.m_denominator;
        return {num, den};
    }

    Fraction operator*(const Fraction& other) const {
        int num = m_numerator * other.m_numerator;
        int den = m_denominator * other.m_denominator;
        return {num, den};
    }

    Fraction operator/(const Fraction& other) const {
        if (other.m_numerator == 0) {
            std::cerr << "Division by zero!\n";
            std::exit(1);
        }
        int num = m_numerator * other.m_denominator;
        int den = m_denominator * other.m_numerator;
        return {num, den};
    }

    bool operator==(const Fraction& other) const {
        return m_numerator == other.m_numerator && m_denominator == other.m_denominator;
    }
};

int main() {
    Fraction a(1, 2);
    Fraction b(3, 4);

    Fraction sum = a + b;
    Fraction difference = a - b;
    Fraction product = a * b;
    Fraction quotient = a / b;

    std::cout << "a = ";
    a.display();
    std::cout << "b = ";
    b.display();
    std::cout << "a + b = ";
    sum.display();
    std::cout << "a - b = ";
    difference.display();
    std::cout << "a * b = ";
    product.display();
    std::cout << "a / b = ";
    quotient.display();

    std::cout << std::boolalpha << "a == b: " << (a == b) << '\n';

    return 0;
}