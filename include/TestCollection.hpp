/**
 * @file TestCollection.hpp
 * @author TL044CN
 * @brief
 * @version 0.1
 * @date 2024-04-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "Testable.hpp"
#include "FlockFlow.hpp"

#include <memory>

using FlockFlow::ThreadPool;

namespace PidgeonPulse {

/**
 * @brief A collection of tests
 */
class TestCollection {
private:
    std::vector<Testable*> mTests;
    std::string mTestCollectionName;

    ThreadPool mThreadPool;
    std::vector<std::future<void>> mTestFutures;

protected:
    /**
     * @brief Create a report for a failed test
     * 
     * @param test the test that failed
     * @return std::string the report
     */
    static std::string createFailReport(Testable* test);

public:

    /**
     * @brief Construct a new Test Collection object
     * 
     * @param name the name of the collection
     */
    TestCollection(std::string name);
    
    /**
     * @brief Destroy the Test Collection object
     */
    ~TestCollection();

    /**
     * @brief Add a test to the collection
     * 
     * @param test the test to add
     */
    void addTest(Testable* test);

    /**
     * @brief Run all the tests in the collection
     */
    void runTests();

    /**
     * @brief Generate a report of the test results
     * 
     * @return std::string the report
     */
    std::string generateReport();

    /**
     * @brief Get the name of the collection
     * 
     * @return std::string the name
     */
    inline std::string getName() const { return mTestCollectionName; }

};

} // namespace PidgeonPulse