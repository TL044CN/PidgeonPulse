#include "Test.hpp"

namespace TT {

void Test::setup(){}
void Test::teardown(){}

void Test::fail() {
    mState = mState | STATE::FAIL_BIT;
}

void Test::fail_with_exception(const std::exception_ptr& e) {
    mException = e;
    mState = mState | STATE::FAIL_BIT | STATE::EXCEPTION_BIT;
}

void Test::fail_with_exception() {
    fail_with_exception(std::current_exception());
}

void Test::assert_true(bool condition) {
    if(condition == false) {
        fail();
    }
}

void Test::assert_false(bool condition) {
    if(condition == true) {
        fail();
    }
}

std::chrono::duration<double> Test::get_duration() const {
    if(static_cast<bool>(mState & STATE::READY_BIT) == false) {
        throw std::runtime_error("Test has not been run yet.");
    }
    std::chrono::duration<double> duration = mEndTime - mStartTime;
    return duration;
}

bool Test::result_ready() const {
    return static_cast<bool>(mState & STATE::READY_BIT);
}

bool Test::get_result() const {
    if(static_cast<bool>(mState & STATE::READY_BIT) == false) {
        throw std::runtime_error("Test has not been run yet.");
    }
    return mState == STATE::PASSED;
}

void Test::operator()() {
    setup();
    mState = STATE::IN_PROGRESS;
    mStartTime = std::chrono::high_resolution_clock::now();
    try {
        run();
    } catch(...) {
        fail_with_exception();
    }
    
    mEndTime = std::chrono::high_resolution_clock::now();
    mState = mState | STATE::READY_BIT;
    teardown();
}

Test::STATE operator&(Test::STATE a, Test::STATE b) {
    return static_cast<Test::STATE>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

Test::STATE operator|(Test::STATE a, Test::STATE b) {
    return static_cast<Test::STATE>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

}