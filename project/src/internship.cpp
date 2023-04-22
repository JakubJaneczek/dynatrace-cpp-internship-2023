#include <chrono>
#include <fstream>
#include <iostream>

#include <date/date.h>
#include <nlohmann/json.hpp>

#include "internship.h"

using json = nlohmann::json;
using namespace date;

namespace internship {
    //Class to store all detected OS with it's values required to be printed (name, version, support period)
    class OperatingSystem
    {
        private:
            std::string m_name;
            double m_supportPeriod;
            std::string m_version;

        public:
            //Constructor
            OperatingSystem(std::string name, double supportPeriod, std::string version)
            {
                this->m_name = name;
                this->m_supportPeriod = supportPeriod;
                this->m_version = version;
            }
            //Function to print necessary info
            void print()
            {
                std::cout << m_name << " " << m_version << " " << m_supportPeriod << "\n";
            }

            //Getters support period 
            double getSupportPeriod() const
            {
                return m_supportPeriod;
            }          
    };

    //custom comparer to sort OperatingSystem instances based on length of support period
    bool compareSupportPeriod(const OperatingSystem& obj1, const OperatingSystem& obj2) 
    {
        return obj1.getSupportPeriod() > obj2.getSupportPeriod();
    }

    //function to parse date string to time_point object
    std::chrono::system_clock::time_point parseDate(const std::string& dateStr) 
    {
        std::tm date = {};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&date, "%Y-%m-%d");
        return std::chrono::system_clock::from_time_t(std::mktime(&date));
    }

    bool checkIfInputIsValid(const json& jsonObject, const std::string& eol, const std::string& releaseDate, const std::string& key3) 
    {
        // Check if all keys are present in the JSON object
        if (!jsonObject.contains(eol) || !jsonObject.contains(releaseDate) || !jsonObject.contains(key3)) 
        {
            return false;
        }

        // Check if all values corresponding to the keys are strings
        if (!jsonObject[eol].is_string() || !jsonObject[releaseDate].is_string() || !jsonObject[key3].is_string()) 
        {
            return false;
        }

        // Check if eol and release date string values are in valid date format "%Y-%m-%d"
        std::string format = "%Y-%m-%d";
        std::tm tm = {};
        std::istringstream ss;

        ss.str(jsonObject[eol].get<std::string>());
        ss >> std::get_time(&tm, format.c_str());
        if (ss.fail()) 
        {
            return false;
        }

        ss.clear();
        ss.str(jsonObject[releaseDate].get<std::string>());
        ss >> std::get_time(&tm, format.c_str());
        if (ss.fail()) 
        {
            return false;
        }
        return true;
    }

    // do not remove this function
    void solution(const std::string& jsonFileName, int elementsCount) {
        
        std::ifstream f(jsonFileName);
        json data = json::parse(f);

        //vector to store OperatinSystem class instances
        std::vector<OperatingSystem> operatingSystems;

        //loop to go through all data in json file
        for (const auto& product : data) {
            //extract only products that are an OS
            bool isOs = product["os"];
            if(isOs)
            {
                //get the OS name
                std::string name = product["name"];
               
                //get all versions of each OS
                for(const auto& iterator : product["versions"])
                {
                    if(checkIfInputIsValid(iterator, "eol", "releaseDate", "cycle"))
                    {
                        std::string version = iterator["cycle"];    
                        std::string releaseDateStr = iterator["releaseDate"];
                        std::string eolStr = iterator["eol"];   

                        //create variables to store dates converted from string
                        std::chrono::system_clock::time_point releaseDate = parseDate(releaseDateStr);
                        std::chrono::system_clock::time_point eol = parseDate(eolStr);

                        //calculate duration of support
                        std::chrono::duration<double> duration = eol - releaseDate;
                        double duration_days = duration.count() / (24 * 60 * 60) + 1;
                        //add valid object to a vector
                        operatingSystems.push_back(OperatingSystem(name, duration_days, version));
                        
                    }                   
                }
            }
        }   
        //sort objects in vector by support period length in descending order
        std::sort(operatingSystems.begin(), operatingSystems.end(), compareSupportPeriod);

        //print results 
        for(int i=0;i< elementsCount; i++)
        {
            operatingSystems.at(i).print();
        }
    }
}