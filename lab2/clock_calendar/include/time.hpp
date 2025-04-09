#ifndef TIME_HPP
#define TIME_HPP

#include "date.hpp"

class Time {
   private:
    int second, minute, hour;
    Date *date = nullptr;

   public:
    Time(int s, int m, int h);
    Time(const std::string &str);
    Time();

    void attachDate(Date *d) { date = d; }

    int getSecond() const { return second; }
    int getMinute() const { return minute; }
    int getHour() const { return hour; }
    int difference(const Time &other) const;
    void modifySeconds(int s);
    void modifyMinutes(int m);
    void modifyHours(int h);

    int toSeconds() const { return second + minute * 60 + hour * 3600; }
    void fromSeconds(int s);

    std::string toString() const;
    void fromString(const std::string &str);
};

#endif