#pragma once
#include <unordered_map>
#include <string>
#include <vector>

class Country {
private:
    std::unordered_map<std::string, std::vector<int>> datesMap;

    std::string countryName;

public:
    Country();
    Country(std::string _countryName);
    void insertDateData(std::string date, int newCases, int cumulativeCases, int newDeaths, int cumulativeDeaths);
    std::string getName();
    std::string getDate();
    void setName(std::string _name);
    int getNewCases(const std::string& date);
    int getCumulativeCases(const std::string& date);
    int getNewDeaths(std::string date);
    int getCumulativeDeaths(std::string date);
    std::unordered_map<std::string, std::vector<int>> GetMap();
};
