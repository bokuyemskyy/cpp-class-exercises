#include "../include/time.hpp"

#include <sstream>

Time::Time(int s, int m, int h) : second(s), minute(m), hour(h) {};
Time::Time(const std::string &str) { fromString(str); };
Time::Time() : second(0), minute(0), hour(0) {};

int Time::difference(const Time &other) const { return toSeconds() - other.toSeconds(); };

void Time::modifySeconds(int s) { fromSeconds(toSeconds() + s); }
void Time::modifyMinutes(int m) { fromSeconds(toSeconds() + m * 60); }
void Time::modifyHours(int h) { fromSeconds(toSeconds() + h * 3600); }

void Time::fromSeconds(int s) {
    second = s % 60;
    minute = (s / 60) % 60;
    hour = s / 3600;
}

std::string Time::toString() const {
    return std::to_string(second) + ":" + std::to_string(minute) + ":" + std::to_string(hour);
};

void Time::fromString(const std::string &str) {
    std::istringstream iss(str);
    std::string token;
    getline(iss, token, ':');
    second = std::stoi(token);
    getline(iss, token, ':');
    minute = std::stoi(token);
    getline(iss, token, ':');
    hour = std::stoi(token);
}
