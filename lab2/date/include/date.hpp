#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>

class Date {
   private:
    int day, month, year;
    bool isLeapYear(int y) const;
    int daysInMonth(int m, int y) const;

   public:
    Date(int d, int m, int y);
    Date(const std::string &str);
    Date();

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int difference(const Date &other) const;
    void modifyDays(int d);
    void modifyMonths(int m);
    void modifyYears(int y);

    int toDays() const;
    void fromDays(int d);

    std::string toString() const;
    void fromString(const std::string &str);
};

#endif