#include "Country.hpp"
Country::Country() {
    countryName = "";
}

Country::Country(std::string _countryName) {
    countryName = _countryName;
}

void Country::insertDateData(std::string date, int newCases, int cumulativeCases, int newDeaths, int cumulativeDeaths) {
    //create the vector that stores COVID data

    std::vector<int> tempVectorData;
    tempVectorData.push_back(newCases);
    tempVectorData.push_back(cumulativeCases);
    tempVectorData.push_back(newDeaths);
    tempVectorData.push_back(cumulativeDeaths);

    //insert into map
    datesMap[date] = tempVectorData;
}

std::string Country::getName() {
    return countryName;
}

std::string Country::getDate() {
    return datesMap.begin()->first;
}

void Country::setName(std::string _name) {
    countryName = _name;
}

int Country::getNewCases(const std::string& date) {
    //get Vector with specified date
    std::vector<int> covidData = datesMap[date];

    //return correct covid data
    return covidData[0];
}

int Country::getCumulativeCases(const std::string& date) {
    //get Vector with specified date
    std::vector<int> covidData = datesMap[date];
    //return correct covid data
    return covidData[1];
}

int Country::getNewDeaths(std::string date) {
    //get Vector with specified date
    std::vector<int> covidData = datesMap[date];
    //return correct covid data
    return covidData[2];
}

int Country::getCumulativeDeaths(std::string date) {
    //get Vector with specified date
    std::vector<int> covidData = datesMap[date];
    //return correct covid data
    return covidData[3];
}


std::unordered_map<std::string, std::vector<int>> Country::GetMap() {
    return datesMap;
}
