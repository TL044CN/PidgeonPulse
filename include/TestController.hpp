/**
 * @file TestController.hpp
 * @author TL044CN
 * @brief 
 * @version 0.1
 * @date 2024-04-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "Singleton.hpp"
#include "TestCollection.hpp"

namespace PidgeonPulse {
    class TestController : Singleton<TestController> {
    private:
        std::vector<TestCollection*> mTestCollections;

    public:
        TestController() = default;
        ~TestController() = default;

        /**
         * @brief Add a TestCollection to the TestController
         * 
         * @param name the name of the TestCollection
         */
        static void addTestCollection(std::string name);

        /**
         * @brief Add a Test to the TestController
         * 
         * Runs the Tests
         */
        static void runTests();

        /**
         * @brief Generate a report of the tests
         * 
         * @return std::string the report
         */
        static std::string generateReport();

    };
} // namespace PidgeonPulse
