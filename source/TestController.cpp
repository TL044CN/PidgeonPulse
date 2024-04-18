#include "TestController.hpp"

using namespace PidgeonPulse;

TestCollection& TestController::addTestCollection(std::string name) {
    auto& controller = TestController::getInstance();
    controller.mTestCollections.push_back(new TestCollection(name));
    return *controller.mTestCollections.back();
}

void TestController::runTests() {
    auto& controller = TestController::getInstance();
    for (auto collection : controller.mTestCollections) {
        collection->runTests();
    }
}

std::string TestController::generateReport() {
    auto& controller = TestController::getInstance();
    std::string report = "PidgeonPulse Unit Test:\n";
    for (auto collection : controller.mTestCollections) {
        report += collection->generateReport();
    }
    return report;
}

TestCollection& TestController::getTestCollection(const std::string& name) {
    auto& controller = TestController::getInstance();
    for (auto collection : controller.mTestCollections) {
        if (collection->getName() == name) {
            return *collection;
        }
    }
    throw std::runtime_error("TestCollection not found");
}
