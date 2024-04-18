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

    /**
     * @brief The main Controller of the Test System
     * 
     * Manages the TestCollections, generates reports, and runs the tests
     */
    class TestController : Singleton<TestController> {
    private:
        std::vector<TestCollection*> mTestCollections;

        friend TestCollection;

    public:
        TestController() = default;
        ~TestController() = default;

        /**
         * @brief Add a TestCollection to the TestController
         * 
         * @param name the name of the TestCollection
         */
        static TestCollection& addTestCollection(std::string name);

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

        /**
         * @brief Get a TestCollection by name
         * 
         * @param name the name of the TestCollection
         * @return TestCollection& the TestCollection
         */
        static TestCollection& getTestCollection(const std::string& name);

    };
} // namespace PidgeonPulse
