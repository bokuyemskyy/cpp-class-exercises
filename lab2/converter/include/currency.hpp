#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <string>
#include <unordered_map>
class Currency {
   private:
    static const std::unordered_map<std::string, float> conversionMultipliers;

   public:
    static float Convert(std::string from = "PLN", std::string to = "PLN", float quantity = 1) {
        return quantity * conversionMultipliers.at(from) / conversionMultipliers.at(to);
    };
};

const std::unordered_map<std::string, float> Currency::conversionMultipliers = {
    {"EUR", 1}, {"USD", 1.1}, {"GBP", 0.8}, {"PLN", 4.2}};
#endif