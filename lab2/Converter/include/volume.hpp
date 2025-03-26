#ifndef VOLUME_HPP
#define VOLUME_HPP

#include <string>
#include <unordered_map>
class Volume {
   private:
    static const std::unordered_map<std::string, float> conversionMultipliers;

   public:
    static float Convert(std::string from = "l", std::string to = "l", float quantity = 1) {
        return quantity * conversionMultipliers.at(from) / conversionMultipliers.at(to);
    };
};

const std::unordered_map<std::string, float> Volume::conversionMultipliers = {
    {"l", 1}, {"ml", 0.001}, {"d3", 1}, {"cm3", 0.001}, {"m3", 1000}};
#endif