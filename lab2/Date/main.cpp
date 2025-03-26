#include <cstdlib>
#include <iostream>

#include "include/date.hpp"

int main(int argc, char *argv[]) {
    Date date(1, 1, 1970);
    Date date2("30/12/2022");
    Date date3("30/12/2024");
    std::cout << "Days passed between " << date.toString() << " and " << date2.toString() << ": "
              << date2.difference(date) << std::endl;
    std::cout << "Days passed between " << date.toString() << " and " << date3.toString() << ": "
              << date3.difference(date) << std::endl;
    std::cout << "Days passed between " << date2.toString() << " and " << date3.toString() << ": "
              << date3.difference(date2) << std::endl;

    return 0;
}