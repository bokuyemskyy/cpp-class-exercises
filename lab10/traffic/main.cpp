#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

struct Light {
    std::string name;
    std::string color;
};

void printState(const std::vector<Light>& lights) {
    std::cout << "---------------------\n";
    for (const auto& l : lights) std::cout << l.name << ": " << l.color << "\n";
}

int main() {
    std::vector<Light> lights = {
        {.name = "North", .color = "RED"},
        {.name = "East", .color = "RED"},
        {.name = "South", .color = "RED"},
        {.name = "West", .color = "RED"},
    };

    const int NS[2] = {0, 2};
    const int EW[2] = {1, 3};

    while (true) {
        for (auto& l : lights) l.color = "RED";
        for (int i : NS) lights[i].color = "GREEN";
        printState(lights);
        std::this_thread::sleep_for(std::chrono::seconds(5));

        for (auto& l : lights) l.color = "RED";
        printState(lights);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        for (int i : EW) lights[i].color = "YELLOW";
        printState(lights);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        for (int i : EW) lights[i].color = "GREEN";
        printState(lights);
        std::this_thread::sleep_for(std::chrono::seconds(5));

        for (auto& l : lights) l.color = "RED";
        printState(lights);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        for (int i : NS) lights[i].color = "YELLOW";
        printState(lights);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return 0;
}
