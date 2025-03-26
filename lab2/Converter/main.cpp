#include <cstdlib>
#include <iostream>

#include "include/currency.hpp"
#include "include/mass.hpp"
#include "include/temperature.hpp"
#include "include/volume.hpp"

int main() {
    std::cout << "10 kg in lb is " << Mass::Convert("kg", "lb", 10) << std::endl;
    std::cout << "10 PLN in EUR is " << Currency::Convert("PLN", "EUR", 10) << std::endl;
    std::cout << "10 C in F is " << Temperature::Convert("C", "F", 10) << std::endl;
    std::cout << "10 l in ml is " << Volume::Convert("l", "ml", 10) << std::endl;
}