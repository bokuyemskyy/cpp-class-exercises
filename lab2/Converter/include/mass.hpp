#ifndef MASS_HPP
#define MASS_HPP

#include <string>
#include <unordered_map>
class Mass {
   private:
    static const std::unordered_map<std::string, float> conversionMultipliers;

   public:
    static float Convert(std::string from = "kg", std::string to = "kg", float quantity = 1) {
        return quantity * conversionMultipliers.at(from) / conversionMultipliers.at(to);
    };
};

const std::unordered_map<std::string, float> Mass::conversionMultipliers = {
    {"kg", 1}, {"g", 0.001}, {"mg", 0.000001}, {"lb", 2.205}, {"oz", 35.274}};

#endif