#include <cstdlib>
#include <iomanip>
#include <unordered_map>

#include "include/date.hpp"
#include "include/time.hpp"

void outputCalendar(const Date &d, const Time &t) {
    std::unordered_map<int, std::string> months = {
        {1, "January"},   {2, "February"}, {3, "March"},     {4, "April"},
        {5, "May"},       {6, "June"},     {7, "July"},      {8, "August"},
        {9, "September"}, {10, "October"}, {11, "November"}, {12, "December"}};

    std::cout << "" << months[d.getMonth()] << " | " << d.getYear() << std::endl;
    for (int i = 1; i < d.daysInMonth(d.getMonth(), d.getYear()); ++i) {
        if (i == d.getDay()) {
            std::cout << std::setw(6) << std::setfill(' ') << "|" + std::to_string(i) + "|";
        } else {
            std::cout << std::setw(6) << std::setfill(' ') << i;
        }
        if (i % 7 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "Date: " << d.toString() << ", Time: " << t.toString() << std::endl;
};

int main(int argc, char *argv[]) {
    Date date(24, 3, 2025);
    Time time(10, 14, 16);
    time.attachDate(&date);
    outputCalendar(date, time);

    date.modifyDays(1);
    date.modifyYears(-3);
    time.modifySeconds(1);
    time.modifyHours(-10);

    std::cout << "\nModified date and time. New calendar: \n" << std::endl;
    outputCalendar(date, time);
    return 0;
}