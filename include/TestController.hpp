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
    public:
        TestController() = default;
        ~TestController() = default;

        /**
         * @brief Add a Test to the TestController
         * 
         * Runs the Tests
         */
        void runTests();
    };
} // namespace PidgeonPulse