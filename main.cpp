#include <fstream>
#include <iostream>
#include <unordered_map>
#include "Country.hpp"
#include "AVL.h"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

std::string displayMenu() {
    std::string message = "1) List countries with available data\n2) Change current country loaded into system\n"
                          "3) Display country's Covid-19 statistics for a certain date\n4) Sort countries by current highest case count\n"
                          "5) Sort countries by current highest Death Count\n6) Sort countries by current lowest case count\n"
                          "7) Sort countries by current lowest Death Count\n8) View load times\n9) Exit the program";
    return message;
}

//receives a given vector of countries and sort it by the country's death count
void SelectionSortDeaths(std::vector<Country> &countryVec){

    for (int i = 0; i < countryVec.size() - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < countryVec.size(); j++) {
            if (countryVec[j].getCumulativeDeaths("10/28/20") < countryVec[min_index].getCumulativeDeaths("10/28/20"))
                min_index = j;
        }

        //make the sorting swap here
        Country temp = countryVec[min_index];
        countryVec[min_index] = countryVec[i];
        countryVec[i] = temp;
    }
}

//selection sort but for the countries cases
void SelectionSortCases(std::vector<Country> &countryVec){

    for (int i = 0; i < countryVec.size() - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < countryVec.size(); j++) {
            if (countryVec[j].getCumulativeCases("10/28/20") < countryVec[min_index].getCumulativeCases("10/28/20"))
                min_index = j;
        }

        //make the sorting swap here
        Country temp = countryVec[min_index];
        countryVec[min_index] = countryVec[i];
        countryVec[i] = temp;
    }
}

//bool is present to determine whether or not to print in ascending or descending order, depending on the user request
void printVectorDeaths(std::vector<Country> &countryVec, bool ascending){

    if(ascending){

        //go through and print all of the vector
        for(int i = 0; i < countryVec.size(); i++){
            std::cout << i+1 << ": " << countryVec[i].getName() << ": " << countryVec[i].getCumulativeDeaths("10/28/20") << " deaths" << std::endl;
        }
    }
    else{
        int count = 1;
        for(int i = countryVec.size() - 1; i >= 0; i--){
            std::cout << count << ": " << countryVec[i].getName() << ": " << countryVec[i].getCumulativeDeaths("10/28/20") << " deaths" << std::endl;
            count++;
        }
    }
}

//bool to determine whether or not to print in ascending or descending order.
void printVectorCases(std::vector<Country> &countryVec, bool ascending){

    if(ascending){
        for(int i = 0; i < countryVec.size(); i++){
            std::cout << i+1 << ": " << countryVec[i].getName() << ": " << countryVec[i].getCumulativeCases("10/28/20") << " cases" << std::endl;
        }
    }
    else{
        int count = 1;
        for(int i = countryVec.size() - 1; i >= 0; i--){
            std::cout << count << ": " << countryVec[i].getName() << ": " << countryVec[i].getCumulativeCases("10/28/20") << " cases" << std::endl;
            count ++;
        }
    }
}

int main(int argc, const char* argv[]) {
    //Read the Covid Data CSV file
    std::ifstream file("CovidData.csv");

    std::unordered_map<std::string, Country> dataMap; //Make the unordered_map
    //helper variables
    std::string line;
    std::string date;
    std::string countryName;
    std::string tempString;
    std::string dateString;
    int newCases = 0;
    int cumulativeCase = 0;
    int newDeaths = 0;
    int cumulativeDeaths = 0;
    int numberOfCountries = 235;
    int numberOfDates = 300;
    int dateCounter = 0;
    //Make AVL Tree
    AVL tree;

    std::getline(file, line); //remove first line

    //Display Welcome message
    std::cout << "\t\t\t\t\t\tWelcome to Disease Data Displayer\n\t\t\t\t\t\t---------------------------------\nUsing this program you will be able to compare and contrast COVID statistics across countries\n\t\t\t\t\t\t\t\tLet's get started!\n\n";
    //Determine whether to load file into AVL Tree or Unordered Map
    int AVLOrUnorderedMap = -1;
    while (AVLOrUnorderedMap != 1 || AVLOrUnorderedMap != 2) {
        std::cout << "Do you want to load Covid-19 data into an AVL Tree or an Unordered Map:\n1) AVL Tree\n2) Unordered Map\n";
        std::cin >> AVLOrUnorderedMap;
        std::cout << std::endl;
        if (AVLOrUnorderedMap == 1 || AVLOrUnorderedMap == 2)
            break;
    }

    std::string structureUsed;

    long long int loadTime;
    long long int retrieveCountryTime;
    long long int sortTime;

    if(AVLOrUnorderedMap==1)
        structureUsed = "AVL";
    else
        structureUsed = "UNORDERED MAP";
    //Display That countries are being loaded into the system
    std::cout << "Countries are currently being loaded into the system, please allow a moment for this to happen...\n\n";
    //traverse file until it is done

    /*
     * Timer start
     */
    auto t1 = Clock::now();

    for (int i = 0; i < numberOfCountries; i++) {
        Country country;
        dateCounter = 0;
        while (std::getline(file, line) && dateCounter < numberOfDates) {
            //Get the Date
            date = line.substr(0, line.find(','));
            line = line.substr(date.size() + 1, line.size());
            //Skip Country Code
            line = line.substr(line.find(',') + 1, line.size());
            //Get Country name
            if (line.at(0) == '"') {
                line = line.substr(1, line.size());
                countryName = line.substr(0, line.find('"'));
                line = line.substr(line.find('"') + 2, line.size());
            }
            else {
                countryName = line.substr(0, line.find(','));
                line = line.substr(countryName.size() + 1, line.size());
            }
            //Skip Country region
            line = line.substr(line.find(',') + 1, line.size());
            //Get newCases
            tempString = line.substr(0, line.find(','));
            newCases = stoi(tempString);
            line = line.substr(tempString.size() + 1, line.size());
            //Get cumulativeCase
            tempString = line.substr(0, line.find(','));
            cumulativeCase = stoi(tempString);
            line = line.substr(tempString.size() + 1, line.size());
            //Get newDeaths
            tempString = line.substr(0, line.find(','));
            newDeaths = stoi(tempString);
            line = line.substr(tempString.size() + 1, line.size());
            //Get cumulative
            tempString = line.substr(0, line.find(','));
            cumulativeDeaths = stoi(tempString);
            //insert data into country
            country.insertDateData(date, newCases, cumulativeCase, newDeaths, cumulativeDeaths);
            //increment date counter
            dateCounter++;
        }
        //add country to AVL Tree or Unordered Map, depending on what the user chose in beginning of program
        country.setName(countryName);
        if (AVLOrUnorderedMap == 1) {  //Add data to AVL Tree
            tree.Insert(tree.GetRoot(), country);
        }
        else if (AVLOrUnorderedMap == 2) {  //Add data to Unordered Map
            dataMap.emplace(countryName, country);
        }

    }
    //Display that countries were successfully loaded into system

    auto t2 = Clock::now();

    loadTime = (t2-t1).count();

    std::cout << "All countries were successfully loaded into system." << std::endl;
    std::cout << std::endl;
    //The country stored in this variable will be the country that is easily accessible and used for displaying

    tree.Inorder(tree.GetRoot());

    //the different statistics for the user inputted date
    Country currentCountry;
    currentCountry.setName("Empty");
    //Display Menu Prompt until user decides to quit
    int option = -1;
    while (option != 8) {
        //Display Current Country loaded into system
        std::cout << std::endl << "Current Country Loaded into System: " << currentCountry.getName() << std::endl << std:: endl;
        //Display Menu Options
        std::cout << "What would you like to do:" << std::endl;
        std::cout << displayMenu();
        std::cin >> option;
        std::cout << std::endl;
        //Different Menu options
        switch (option) {
        case 1:
            //Traverse entire Map or AVL Tree then printing each countries name

            if(AVLOrUnorderedMap == 1){  //code for traversing AVL tree, want inorder Traversal
                tree.Inorder(tree.GetRoot());
            }
            else if(AVLOrUnorderedMap == 2){  //code for use of traversing Unordered Map
                //establish vector
                //iter through map, add country to vector
                //sort vector
                //print new sorted vector

                std::vector<std::string> orderPrint;

                //load the vector with all the countries from the map, so that we can sort after
                for(auto iter = dataMap.begin(); iter != dataMap.end(); iter++){
                    orderPrint.push_back(iter->first);
                }

                //sort the unordered map traversal
                for (int i = 0; i < orderPrint.size() - 1; i++) {
                    int min_index = i;
                    for (int j = i + 1; j < orderPrint.size(); j++) {
                        if (orderPrint[j] < orderPrint[min_index])
                            min_index = j;
                    }

                    std::string temp = orderPrint[min_index];
                    orderPrint[min_index] = orderPrint[i];
                    orderPrint[i] = temp;
                }

                //print out properly ordered vector
                for(int i = 0; i < orderPrint.size(); i++){
                    std::cout << orderPrint[i] << std::endl;
                }
            }
            break;

        case 2:
            //for updating the current country loaded into system
            //the user will then be asked to type in what country they want

            std::cout << "Which country would you like to use?" << std::endl;
            std::ws(std::cin); //read the white space so that getline is not skipped at the next line
            getline(std::cin, countryName);

            //start timer
            t1 = Clock::now();

            if(AVLOrUnorderedMap == 1){  //code for use of AVL
                //search through main AVL to find and obtain COUNTRY obj,
                tree.AssignCountry(tree.GetRoot(), countryName, currentCountry); //uses country REFERENCE to assign object, traversal based on string
            }

            else if(AVLOrUnorderedMap == 2){  //code for use of Unordered Map
                    currentCountry = dataMap[countryName];
            }

            t2 = Clock::now();

            //set time
            retrieveCountryTime = (t2-t1).count();
            break;

        case 3:
            //after user chooses option 3
            //user gets asked to enter a date in the MM/DD/YY format
            //then with the current country loaded, displays data

            std::cout << "Enter data of interest using \"MM/DD/YY\" format (Do not include leading zeroes in day or month): ";
            std::cin >> dateString;

            std::cout << "New Cases: " << currentCountry.getNewCases(dateString) << std::endl;
            std::cout << "Cumulative Cases: " << currentCountry.getCumulativeCases(dateString) << std::endl;
            std::cout << "New Deaths: " << currentCountry.getNewDeaths(dateString) << std::endl;
            std::cout << "Cumulative Deaths: " << currentCountry.getCumulativeDeaths(dateString) << std::endl;

            break;

        case 4:
            //sort by highest case count

            //timer start
            t1 = Clock::now();

            if(AVLOrUnorderedMap == 1){  // AVL Tree
                //traverse func
                //push back to reference of vector of Countries
                //sort this vector based off country->getCaseCount

                std::vector<Country> caseCounts;
                tree.LoadCountries(tree.GetRoot(), caseCounts);  //load up all Countries into this vector
                SelectionSortCases(caseCounts); //use function call to sort loaded vector
                //print sorted vector
                printVectorCases(caseCounts, false); //want in descending order

            }

            else if(AVLOrUnorderedMap == 2){  // Unordered Map
                //same deal as AVL, but make iter to iterate through map

                std::vector<Country> caseCounts;

                //for loop to push back countries into vector
                for(auto iter = dataMap.begin(); iter!= dataMap.end(); iter++){
                    caseCounts.push_back(iter->second);
                }
                SelectionSortCases(caseCounts);
                printVectorCases(caseCounts, false);

            }

            //timer end and set Var
            t2 = Clock::now();
            sortTime = (t2-t1).count();
            break;

        case 5:
            //sort deaths
            if (AVLOrUnorderedMap == 1) {
                std::vector<Country> deathCounts;
                tree.LoadCountries(tree.GetRoot(), deathCounts);
                SelectionSortDeaths(deathCounts);
                printVectorDeaths(deathCounts, false);
            }
            else if (AVLOrUnorderedMap == 2) {
                std::vector<Country> deathCounts;
                for(auto iter = dataMap.begin(); iter!= dataMap.end(); iter++) {
                    deathCounts.push_back(iter->second);
                }
                SelectionSortDeaths(deathCounts);
                printVectorDeaths(deathCounts, false);
            }
            break;

        case 6:
            //lowest case count

            if(AVLOrUnorderedMap == 1){

                std::vector<Country> caseCount;
                tree.LoadCountries(tree.GetRoot(), caseCount);
                SelectionSortCases(caseCount);
                printVectorCases(caseCount, true);
            }

            else if(AVLOrUnorderedMap == 2){
                std::vector<Country> caseCount;
                for(auto iter = dataMap.begin(); iter!= dataMap.end(); iter++){
                    caseCount.push_back(iter->second);
                }
                SelectionSortCases(caseCount);
                printVectorCases(caseCount, true);
            }
            break;
        case 7:
            //lowest death count

            if(AVLOrUnorderedMap == 1){

                std::vector<Country> deathCount;
                tree.LoadCountries(tree.GetRoot(), deathCount);
                SelectionSortDeaths(deathCount);
                printVectorDeaths(deathCount, true);
            }

            else if(AVLOrUnorderedMap == 2){
                std::vector<Country> deathCount;
                //load vector
                for(auto iter = dataMap.begin(); iter!= dataMap.end(); iter++){
                    deathCount.push_back(iter->second);
                }
                SelectionSortDeaths(deathCount);
                printVectorDeaths(deathCount, true);
            }
            break;
        case 8:
            std::cout << "Time taken to load the " << structureUsed << ": " << loadTime/1000000 << " milliseconds" << std::endl
                      << "Time taken to load a new country: " << retrieveCountryTime/10 <<" nanoseconds" << std::endl
                      << "Time taken to sort " << structureUsed << ": " << sortTime/1000000 << " milliseconds" << std::endl;
        case 9:
                break;
        default:
            std::cout << "Something Broke" << std::endl;
            break;
        }
    }

    //Display Thank you Message
    std::cout << "Thank you for using Disease Data Displayer!" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    return 0;
}
