#include <cassert>
#include <cmath>
#include <iostream>
#include <numbers>
#include <variant>

constexpr float PI = std::numbers::pi_v<float>;

struct Circle {
    float radius;

    [[nodiscard]] float area() const { return PI * radius * radius; }
    [[nodiscard]] float perimeter() const { return 2 * PI * radius; }
};

struct Rectangle {
    float width;
    float height;

    [[nodiscard]] float area() const { return width * height; }
    [[nodiscard]] float perimeter() const { return 2 * (width + height); }
};

struct Triangle {
    float a, b, c;

    [[nodiscard]] float area() const {
        float s = (a + b + c) / 2;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
    [[nodiscard]] float perimeter() const { return a + b + c; }
};

using Shape = std::variant<Circle, Rectangle, Triangle>;

float getArea(const Shape& shape) {
    return std::visit([](const auto& s) { return s.area(); }, shape);
}

float getPerimeter(const Shape& shape) {
    return std::visit([](const auto& s) { return s.perimeter(); }, shape);
}

void printShape(const Shape& shape) {
    std::visit(
        [](const auto& s) {
            std::cout << "Area: " << s.area() << ", Perimeter: " << s.perimeter() << '\n';
        },
        shape);
}

int main() {
    Shape c = Circle{5.0F};
    Shape r = Rectangle{.width = 4.0f, .height = 6.0f};
    Shape t = Triangle{.a = 3.0f, .b = 4.0f, .c = 5.0f};

    std::cout << "Circle: ";
    printShape(c);

    std::cout << "Rectangle: ";
    printShape(r);

    std::cout << "Triangle: ";
    printShape(t);

    return 0;
}
