#include "Testable.hpp"

namespace PidgeonPulse {

void Testable::setup(){}
void Testable::teardown(){}

void Testable::fail(const char* file, int line, bool fatal) {
    mFailInfos.push_back({file, line, nullptr});
    mState = mState | STATE::FAIL_BIT;
    if(fatal == true)
        throw FatalException(file, line);
}

void Testable::fail() {
    fail(nullptr, 0, false);
}

void Testable::fail_with_exception(const char* file, int line, const std::exception_ptr& e, bool fatal) {
    mState = mState | STATE::FAIL_BIT | STATE::EXCEPTION_BIT;
    mFailInfos.push_back({file, line, e});
    if(fatal == true)
        throw FatalException(file, line);
}

void Testable::fail_with_exception() {
    fail_with_exception(nullptr,0,std::current_exception(), true);
}

void Testable::assert_true(bool condition) {
    if(condition == false) {
        fail(__FILENAME__, __LINE__, true);
    }
}

void Testable::assert_false(bool condition) {
    if(condition == true) {
        fail(__FILENAME__, __LINE__, true);
    }
}

std::chrono::duration<double> Testable::get_duration() const {
    if(static_cast<bool>(mState & STATE::READY_BIT) == false) {
        throw std::runtime_error("Test has not been run yet.");
    }
    std::chrono::duration<double> duration = mEndTime - mStartTime;
    return duration;
}

bool Testable::result_ready() const {
    return static_cast<bool>(mState & STATE::READY_BIT);
}

bool Testable::get_result() const {
    if(static_cast<bool>(mState & STATE::READY_BIT) == false) {
        throw std::runtime_error("Test has not been run yet.");
    }
    return mState == STATE::PASSED;
}

void Testable::operator()() {
    setup();
    mState = STATE::IN_PROGRESS;
    mStartTime = std::chrono::high_resolution_clock::now();
    try {
        run();
    } catch(FatalException& e) {

    } catch(...) {
        fail_with_exception(__FILENAME__, __LINE__, std::current_exception(), false);
    }
    
    mEndTime = std::chrono::high_resolution_clock::now();
    mState = mState | STATE::READY_BIT;
    teardown();
}

Testable::STATE operator&(Testable::STATE a, Testable::STATE b) {
    return static_cast<Testable::STATE>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

Testable::STATE operator|(Testable::STATE a, Testable::STATE b) {
    return static_cast<Testable::STATE>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

}