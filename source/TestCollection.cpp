#include "TestCollection.hpp"

namespace PidgeonPulse {

TestCollection::TestCollection(std::string name): mTestCollectionName(name) {
    mThreadPool.pause();
}

TestCollection::~TestCollection() {
    mTests.clear();
}


std::string TestCollection::createFailReport(Testable* test) {
    std::string report = "\tTest failed: " + test->get_name() + "\n";

    for ( auto& failInfo : test->get_fail_infos() ) {
        report += "\t File: " + std::string(failInfo.file) + ":" + std::to_string(failInfo.line) + "\n";
        if ( failInfo.exception ) {
            try {
                std::rethrow_exception(failInfo.exception);
            } catch ( const std::exception& e ) {
                report += std::string("\t Exception: ") + e.what() + "\n";
            } catch ( ... ) {
                report += "\t Exception: Unknown exception\n";
            }
        }
        report += "\n";
    }

    return report;
}

void TestCollection::addTest(Testable* test) {
    mTests.push_back(test);
    mTestFutures.push_back(mThreadPool.queueJob(
        [test]() {
            (*test)();
        })
    );
}

void TestCollection::runTests() {
    mThreadPool.resume();

    for ( auto& future : mTestFutures ) {
        future.wait();
    }
}

std::string TestCollection::generateReport() {
    std::string report = "Test Collection: " + mTestCollectionName + "\n";

    if ( mThreadPool.hasTasks() ) {
        runTests();
    }

    uint32_t testCount = mTests.size();
    uint32_t failedCount = 0;

    for ( auto& test : mTests ) {
        if ( !test->get_result() ) {
            failedCount++;
            report += createFailReport(test);
        }
    }

    report += "Stats: failed " + std::to_string(failedCount) + " of " + std::to_string(testCount) + " tests\n";

    return report;
}

} // namespace PidgeonPulse