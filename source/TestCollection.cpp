#include "TestCollection.hpp"

namespace PidgeonPulse {

TestCollection::TestCollection(std::string name): mTestCollectionName(name) {}

void TestCollection::addTest(Testable* test) {
    mTests.push_back(test);
}

void TestCollection::runTests() {
    for ( auto& test : mTests ) {
        test->run();
    }
}

} // namespace PidgeonPulse