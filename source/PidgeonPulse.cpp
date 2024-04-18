#include "PidgeonPulse.hpp"
#include "TestController.hpp"

#include <fstream>

#ifdef PIDGEON_PULSE_CONFIG_MAIN

using namespace PidgeonPulse;

int main(int argc, char** argv) {

    std::ofstream logFile("test.report");

    TestController::runTests();
    logFile << TestController::generateReport();

    logFile.close();

    return EXIT_SUCCESS;
}

#endif