#include "internship.h"

namespace internship {
    OperatingSystem::OperatingSystem(std::string name, double supportPeriod, std::string version)
    {
        this->m_name = name;
        this->m_supportPeriod = supportPeriod;
        this->m_version = version;
    }

    void OperatingSystem::print()
    {
        std::cout << m_name << " " << m_version << " " << m_supportPeriod << "\n";
    }

    double OperatingSystem::getSupportPeriod() const
    {
        return m_supportPeriod;
    }    

    bool compareSupportPeriod(const OperatingSystem& obj1, const OperatingSystem& obj2) 
    {
        return obj1.getSupportPeriod() > obj2.getSupportPeriod();
    }

    std::chrono::system_clock::time_point parseDate(const std::string& dateString) 
    {
        const std::string format = "%Y-%m-%d";
        std::tm date = {};
        std::istringstream ss(dateString);
        ss >> std::get_time(&date, format.c_str());
        return std::chrono::system_clock::from_time_t(std::mktime(&date));
    }

    bool checkCorrectDateForm(const std::string& dateString)
    {
        const std::string format = "%Y-%m-%d";
        std::tm date = {};
        std::istringstream ss(dateString);
        ss >> std::get_time(&date, format.c_str());
        return !ss.fail();
    }

    bool checkIfInputIsValid(const json& jsonObject, const std::string& eol, const std::string& releaseDate, const std::string& version) 
    {
        if (!jsonObject.contains(eol) || !jsonObject.contains(releaseDate) || !jsonObject.contains(version))         
            return false;
        
        if (!jsonObject[eol].is_string() || !jsonObject[releaseDate].is_string() || !jsonObject[version].is_string())         
            return false;

        if (!checkCorrectDateForm(jsonObject[eol].get<std::string>()))
            return false;
        

        if (!checkCorrectDateForm(jsonObject[releaseDate].get<std::string>()))
            return false;
        
        return true;
    }

    // do not remove this function
    void solution(const std::string& jsonFileName, int elementsCount) {
        
        std::ifstream f(jsonFileName);
        json data = json::parse(f);
        std::vector<OperatingSystem> operatingSystems;

        for (const auto& product : data) {
            bool isOs = product["os"];
            if(isOs)
            {
                std::string name = product["name"];
               
                for(const auto& iterator : product["versions"])
                {
                    if(checkIfInputIsValid(iterator, "eol", "releaseDate", "cycle"))
                    {
                        std::string version = iterator["cycle"];    
                        std::string releaseDateStr = iterator["releaseDate"];
                        std::string eolStr = iterator["eol"];   

                        std::chrono::duration<double> duration = parseDate(eolStr) - parseDate(releaseDateStr);
                        double duration_days = duration.count() / (24 * 60 * 60) + 1;
                        operatingSystems.push_back(OperatingSystem(name, duration_days, version));
                        
                    }                   
                }
            }
        }   
        std::sort(operatingSystems.begin(), operatingSystems.end(), compareSupportPeriod);

        for(int i=0;i< elementsCount; i++)
        {
            operatingSystems.at(i).print();
        }
    }

}