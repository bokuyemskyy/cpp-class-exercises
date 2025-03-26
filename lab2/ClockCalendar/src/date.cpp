#include "../include/date.hpp"

#include <sstream>

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}
Date::Date(const std::string &str) { fromString(str); }
Date::Date() : day(1), month(1), year(1970) {}

bool Date::isLeapYear(int y) const { return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); }

int Date::daysInMonth(int m, int y) const {
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (month == 2 && isLeapYear(y)) ? 29 : days[m - 1];
}

int Date::toDays() const {
    int totalDays = 0;
    for (int y = 1970; y < year; ++y) {
        totalDays += isLeapYear(y) ? 366 : 365;
    }
    for (int m = 1; m < month; ++m) {
        totalDays += daysInMonth(m, year);
    }
    totalDays += day;
    return totalDays;
}

void Date::fromDays(int d) {
    year = 0;
    month = 1;
    day = 1;

    while (d >= (isLeapYear(year) ? 366 : 365)) {
        d -= isLeapYear(year) ? 366 : 365;
        year++;
    }

    while (d >= daysInMonth(month, year)) {
        d -= daysInMonth(month, year);
        month++;
    }

    day = d;
    year += 1970;
}

int Date::difference(const Date &other) const { return toDays() - other.toDays(); }

void Date::modifyDays(int d) { fromDays(toDays() + d); }

void Date::modifyMonths(int m) {
    month += m;
    while (month > 12) {
        month -= 12;
        year++;
    }
    while (month < 1) {
        month += 12;
        year--;
    }
}

void Date::modifyYears(int y) { year += y; }

std::string Date::toString() const {
    return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
};

void Date::fromString(const std::string &str) {
    std::istringstream iss(str);
    std::string token;
    getline(iss, token, '/');
    day = std::stoi(token);
    getline(iss, token, '/');
    month = std::stoi(token);
    getline(iss, token, '/');
    year = std::stoi(token);
}
