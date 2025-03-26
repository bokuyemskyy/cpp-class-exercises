#ifndef TEMPERATURE_HPP
#define TEMPERATURE_HPP

#include <string>
#include <unordered_map>
class Temperature {
   private:
    static const std::unordered_map<std::string, float> conversionMultipliers;

   public:
    static float Convert(std::string from = "C", std::string to = "C", float quantity = 1) {
        return quantity * conversionMultipliers.at(from) / conversionMultipliers.at(to);
    };
};

const std::unordered_map<std::string, float> Temperature::conversionMultipliers = {
    {"C", 1}, {"F", 1.8}, {"K", 273.15}};

#endif