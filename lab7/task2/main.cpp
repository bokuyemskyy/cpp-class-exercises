#include <cmath>
#include <iostream>
#include <memory>
#include <numbers>
#include <vector>

class Shape {
   public:
    [[nodiscard]] virtual double area() const = 0;
    [[nodiscard]] virtual double perim() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
   private:
    double m_r;

   public:
    Circle(double r) : m_r(r) {}
    [[nodiscard]] double area() const override { return std::numbers::pi * m_r * m_r; }
    [[nodiscard]] double perim() const override { return 2 * std::numbers::pi * m_r; }
};

class Rectangle : public Shape {
   private:
    double m_w, m_h;

   public:
    Rectangle(double w, double h) : m_w(w), m_h(h) {}
    [[nodiscard]] double area() const override { return m_w * m_h; }
    [[nodiscard]] double perim() const override { return 2 * (m_w + m_h); }
};

class Triangle : public Shape {
   private:
    double m_a, m_b, m_c;

   public:
    Triangle(double a, double b, double c) : m_a(a), m_b(b), m_c(c) {}
    [[nodiscard]] double area() const override {
        double s = (m_a + m_b + m_c) / 2;
        return sqrt(s * (s - m_a) * (s - m_b) * (s - m_c));
    }
    [[nodiscard]] double perim() const override { return m_a + m_b + m_c; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>(3));
    shapes.push_back(std::make_unique<Rectangle>(4, 5));
    shapes.push_back(std::make_unique<Triangle>(3, 4, 5));

    for (const auto& shape : shapes) {
        std::cout << "Area: " << shape->area() << ", perimeter: " << shape->perim() << '\n';
    }

    return 0;
}