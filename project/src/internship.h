#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <date/date.h>
#include <nlohmann/json.hpp>
#include <gtest/gtest.h>

using json = nlohmann::json;

namespace internship {
    //class to store all detected OS with it's values required to be printed (name, version, support period)
    class OperatingSystem
    {
        private:
            std::string m_name;
            double m_supportPeriod;
            std::string m_version;

        public:
            //constructor
            OperatingSystem(std::string name, double supportPeriod, std::string version);
            
            //function to print necessary info
            void print();

            //getter for support period 
            double getSupportPeriod() const;
    };

    //custom comparer to sort OperatingSystem instances based on length of support period
    bool compareSupportPeriod(const OperatingSystem& obj1, const OperatingSystem& obj2);

    //function to parse date string to time_point object
    std::chrono::system_clock::time_point parseDate(const std::string& dateStr);

    bool checkIfInputIsValid(const json& jsonObject, const std::string& eol, const std::string& releaseDate, const std::string& version);

    // do not remove this function
    void solution(const std::string& jsonFileName, int elementsCount);
}