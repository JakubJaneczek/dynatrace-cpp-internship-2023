#include "../src/internship.h"

namespace internship
{
  class OperatingSystemTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
  };

  TEST_F(OperatingSystemTest, CheckIfInputIsValid) {
    json jsonObject = {
      {"eol", "2023-04-22"},
      {"releaseDate", "2021-09-01"},
      {"cycle", "v1.0"}
    };
    bool result = checkIfInputIsValid(jsonObject, "eol", "releaseDate", "cycle");
    EXPECT_TRUE(result);

    jsonObject["eol"] = "2023/04/22";  //invalid date format
    result = checkIfInputIsValid(jsonObject, "eol", "releaseDate", "cycle");
    EXPECT_FALSE(result);

    jsonObject.erase("releaseDate");  //remove "releaseDate" key
    result = checkIfInputIsValid(jsonObject, "eol", "releaseDate", "cycle");
    EXPECT_FALSE(result);

    jsonObject = {
      {"eol", 12345},   //invalid type
      {"releaseDate", "2021-09-01"},
      {"cycle", "v1.0"}
    };
    result = checkIfInputIsValid(jsonObject, "eol", "releaseDate", "cycle");
    EXPECT_FALSE(result);
  }

  TEST_F(OperatingSystemTest, SortOperatingSystems) {
      OperatingSystem os1("Windows", 365, "10.0");
      OperatingSystem os2("macOS", 730, "12.0");
      OperatingSystem os3("Ubuntu", 180, "20.04");
      OperatingSystem os4("Fedora", 90, "35");

      std::vector<OperatingSystem> operatingSystems;
      operatingSystems.push_back(os1);
      operatingSystems.push_back(os2);
      operatingSystems.push_back(os3);
      operatingSystems.push_back(os4);

      std::sort(operatingSystems.begin(), operatingSystems.end(), compareSupportPeriod);

      EXPECT_EQ(operatingSystems[0].getSupportPeriod(), 730); //os2 should be first with support period 730
      EXPECT_EQ(operatingSystems[1].getSupportPeriod(), 365); //os1 should be second with support period 365
      EXPECT_EQ(operatingSystems[2].getSupportPeriod(), 180); //os3 should be third with support period 180
      EXPECT_EQ(operatingSystems[3].getSupportPeriod(), 90);  //os4 should be fourth with support period 90
  }
}

