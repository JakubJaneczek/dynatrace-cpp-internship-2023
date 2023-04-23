#include "../src/internship.h"

namespace internship
{
  //define a test fixture for the OperatingSystem class
  class OperatingSystemTest : public ::testing::Test {
  protected:
    void SetUp() override {
      //set up any necessary data for the tests
    }

    void TearDown() override {
      //clean up any resources used by the tests
    }
  };

  //define a test case for the checkIfInputIsValid function
  TEST_F(OperatingSystemTest, CheckIfInputIsValid) {
    //test case 1: Test with valid input
    json jsonObject = {
      {"eol", "2023-04-22"},
      {"releaseDate", "2021-09-01"},
      {"cycle", "v1.0"}
    };
    bool result = checkIfInputIsValid(jsonObject, "eol", "releaseDate", "cycle");
    EXPECT_TRUE(result);

    //test case 2: Test with invalid date format
    jsonObject["eol"] = "2023/04/22";  // Invalid date format
    result = checkIfInputIsValid(jsonObject, "eol", "releaseDate", "cycle");
    EXPECT_FALSE(result);

    //test case 3: Test with missing key in JSON object
    jsonObject.erase("releaseDate");  // Remove "releaseDate" key
    result = checkIfInputIsValid(jsonObject, "eol", "releaseDate", "cycle");
    EXPECT_FALSE(result);

    //test case 4: Test with non-string values for keys
    jsonObject = {
      {"eol", 12345},
      {"releaseDate", "2021-09-01"},
      {"cycle", "v1.0"}
    };
    result = checkIfInputIsValid(jsonObject, "eol", "releaseDate", "cycle");
    EXPECT_FALSE(result);
  }

  TEST_F(OperatingSystemTest, SortOperatingSystems) {
      //create some OperatingSystem objects with different support periods
      OperatingSystem os1("Windows", 365, "10.0");
      OperatingSystem os2("macOS", 730, "12.0");
      OperatingSystem os3("Ubuntu", 180, "20.04");
      OperatingSystem os4("Fedora", 90, "35");

      //create a vector to store the OperatingSystem objects
      std::vector<OperatingSystem> operatingSystems;
      operatingSystems.push_back(os1);
      operatingSystems.push_back(os2);
      operatingSystems.push_back(os3);
      operatingSystems.push_back(os4);

      //sort the OperatingSystem objects using the compareSupportPeriod() function
      std::sort(operatingSystems.begin(), operatingSystems.end(), compareSupportPeriod);

      //check if the OperatingSystem objects are sorted correctly based on support period
      EXPECT_EQ(operatingSystems[0].getSupportPeriod(), 730); //os2 should be first with support period 730
      EXPECT_EQ(operatingSystems[1].getSupportPeriod(), 365); //os1 should be second with support period 365
      EXPECT_EQ(operatingSystems[2].getSupportPeriod(), 180); //os3 should be third with support period 180
      EXPECT_EQ(operatingSystems[3].getSupportPeriod(), 90);  //os4 should be fourth with support period 90
  }
}

