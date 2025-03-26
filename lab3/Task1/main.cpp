#include <string>
#include <vector>
#include <iostream>

int main() {
    auto i = int(0);
    auto d = double(3);
    auto s = std::string("3");

    auto vec = std::vector<int>{1, 2, 3};

    for (const auto& elem : vec) {
        i += elem;
    }

    auto* const p = &i;
    const auto& r = d;

    const int tryToModify = i;
    tryToModify++;
    // this causes compiler error
}