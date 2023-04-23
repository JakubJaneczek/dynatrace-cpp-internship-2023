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
    class OperatingSystem
    {
        private:
            std::string m_name;
            double m_supportPeriod;
            std::string m_version;

        public:
            OperatingSystem(std::string name, double supportPeriod, std::string version);
            
            void print();

            double getSupportPeriod() const;
    };

    bool compareSupportPeriod(const OperatingSystem& obj1, const OperatingSystem& obj2);

    std::chrono::system_clock::time_point parseDate(const std::string& dateStr);

    bool checkIfInputIsValid(const json& jsonObject, const std::string& eol, const std::string& releaseDate, const std::string& version);

    void solution(const std::string& jsonFileName, int elementsCount);

    bool checkCorrectDateForm(const std::string& dateString);
}