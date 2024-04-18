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

#include <memory>

namespace PidgeonPulse {

/**
 * @brief A collection of tests
 */
class TestCollection {
private:
    std::vector<Testable*> mTests;
    std::string mTestCollectionName;

public:
    TestCollection(std::string name);
    ~TestCollection() = default;

    void addTest(Testable* test);
    void runTests();

};

} // namespace PidgeonPulse