#include <catch2/catch.hpp>
#include "TestController.hpp"

TEST_CASE("Test TestController", "[TestController]") {
    PidgeonPulse::TestController& tc = PidgeonPulse::TestController::getInstance();

    SECTION("Test addTestCollection") {
        PidgeonPulse::TestCollection& tc1 = tc.addTestCollection("Test1");
        REQUIRE(tc.getTestCollection("Test1") == &tc1);
    }

    SECTION("Test getTestCollection") {
        PidgeonPulse::TestCollection& tc1 = tc.addTestCollection("Test1");
        REQUIRE(tc.getTestCollection("Test1") == &tc1);

        PidgeonPulse::TestCollection& tc2 = tc.addTestCollection("Test2");
        REQUIRE(tc.getTestCollection("Test2") == &tc2);

        REQUIRE_THROWS_AS(tc.getTestCollection("NonExistentTest"), std::runtime_error);
    }

    SECTION("Test runTests") {
        // Add test cases to the test collections
        PidgeonPulse::TestCollection& tc1 = tc.addTestCollection("Test1");
        // Assuming addTestCase is a method in TestCollection that adds a test case
        tc1.addTestCase("TestCase1", []() { return true; });

        // Run the tests
        tc.runTests();

        // Verify the results
        // This will depend on how you can access and check the test results in TestController
        // For example, if you have a method to get a test result by name, you might do:
        REQUIRE(tc.getTestResult("Test1", "TestCase1") == true);
    }

    SECTION("Test generateReport") {
        // Add test cases to the test collections
        PidgeonPulse::TestCollection& tc1 = tc.addTestCollection("Test1");
        tc1.addTestCase("TestCase1", []() { return true; });

        // Generate the report
        std::string report = tc.generateReport();

        // Verify the contents of the report
        // This will depend on the format of the report
        // For example, if the report is a string that includes the names of the test collections and test cases, you might do:
        REQUIRE(report.find("Test1") != std::string::npos);
        REQUIRE(report.find("TestCase1") != std::string::npos);
    }
}