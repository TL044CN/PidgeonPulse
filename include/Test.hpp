/**
 * @file Test.hpp
 * @author TL044CN
 * @brief 
 * @version 0.1
 * @date 2024-04-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <chrono>

namespace TT {

/**
 * Unit Test base class 
 * @brief Unit Test base class
 * 
 */
/**
 * @brief The Test class represents a base class for unit tests.
 * 
 * This class provides a common interface for setting up, tearing down, and running tests.
 * Derived classes should implement the run() method to define the specific test logic.
 */
class Test {
private:
    enum class STATE {
        PROGRESS_BIT        = 0b0001,
        READY_BIT           = 0b0010,
        FAIL_BIT            = 0b0100,
        NOT_RUN             = 0b0000,
        EXCEPTION_BIT       = 0b1000,
        IN_PROGRESS         = PROGRESS_BIT,
        FAILED              = READY_BIT | FAIL_BIT,
        FAIL_WITH_EXCEPTION = READY_BIT | FAIL_BIT | EXCEPTION_BIT,
        PASSED              = READY_BIT
    };

    friend STATE operator&(STATE a, STATE b);
    friend STATE operator|(STATE a, STATE b);

    STATE mState = STATE::NOT_RUN;
    std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> mEndTime;

    std::exception_ptr mException;

protected:
    /**
     * @brief Mark the test as failed.
     * 
     * This method is called to mark the test as failed.
     */
    void fail();

    /**
     * @brief Mark the test as failed with an exception.
     * @note This method has to be called from within a catch block.
     * @param e the exception that caused the test to fail.
     */
    void fail_with_exception(const std::exception_ptr& e);
    void fail_with_exception();


    /**
     * @brief Assert that a condition is true.
     * 
     * This method is called to assert that a condition is true.
     * If the condition is false, the test is marked as failed.
     * 
     * @param condition the condition to assert.
     */
    void assert_true(bool condition);

    /**
     * @brief Assert that a condition is false.
     * 
     * This method is called to assert that a condition is false.
     * If the condition is true, the test is marked as failed.
     * 
     * @param condition the condition to assert.
     */
    void assert_false(bool condition);

    /**
     * @brief Assert that two values are equal.
     * 
     * This method is called to assert that two values are equal.
     * If the values are not equal, the test is marked as failed.
     * 
     * @tparam T the type of the values to compare.
     * @param a the first value to compare.
     * @param b the second value to compare.
     */
    template<typename T>
    void assert_eq(const T& a, const T& b) {
        if(a != b) {
            fail();
        }
    }

    /**
     * @brief Assert that two values are not equal.
     * 
     * This method is called to assert that two values are not equal.
     * If the values are equal, the test is marked as failed.
     * 
     * @tparam T the type of the values to compare.
     * @param a the first value to compare.
     * @param b the second value to compare.
     */
    template<typename T>
    void assert_ne(const T& a, const T& b) {
        if(a == b) {
            fail();
        }
    }

    /**
     * @brief Assert that a function throws an exception of a specific type.
     * 
     * This method is called to assert that a function throws an exception of a specific type.
     * If the function does not throw the expected exception, the test is marked as failed.
     * 
     * @tparam Func the type of the function to call.
     * @tparam Ex the type of the exception to expect.
     * @param function the function to call.
     * @param expected_exception the expected exception type.
     */
    template<typename Func, typename Ex>
    void assert_throw(Func function, Ex expected_exception) {
        try {
            function();
            fail();
        } catch(Ex&) {

        } catch(...) {
            fail_with_exception();
        }
    }

    /**
     * @brief Assert that a function does not throw an exception.
     * 
     * This method is called to assert that a function does not throw an exception.
     * If the function throws an exception, the test is marked as failed.
     * 
     * @tparam Func the type of the function to call.
     * @param function the function to call.
     */
    template<typename Func>
    void assert_no_throw(Func function) {
        try {
            function();
        } catch(...) {
            fail_with_exception();
        }
    }

    /**
     * @brief Assert that a function throws an exception.
     * 
     * This method is called to assert that a function throws an exception.
     * If the function does not throw an exception, the test is marked as failed.
     * 
     * @tparam Func the type of the function to call.
     * @param function the function to call.
     */
    template<typename Func>
    void assert_any_throw(Func function) {
        try {
            function();
            fail();
        } catch(...) {

        }
    }

public:
    /**
     * @brief Construct a new Test object.
     * 
     * This is the default constructor for the Test class.
     */
    Test();

    /**
     * @brief Destroy the Test object.
     * 
     * This is the destructor for the Test class.
     */
    virtual ~Test() = default;

    /**
     * @brief Setup the test.
     * 
     * This method is called before running the test.
     * Derived classes can override this method to perform any necessary setup operations.
     */
    virtual void setup();

    /**
     * @brief Teardown the test.
     * 
     * This method is called after running the test.
     * Derived classes can override this method to perform any necessary cleanup operations.
     */
    virtual void teardown();

    /**
     * @brief Run the test.
     * 
     * This method must be implemented by derived classes to define the specific test logic.
     * It should contain the code that executes the test and verifies the expected behavior.
     * 
     * @return * void 
     */
    virtual void run() = 0;

    /**
     * @brief get the Duration of the test.
     * 
     * @return std::chrono::duration<double> the duration of the test.
     */
    std::chrono::duration<double> get_duration() const;

    /**
     * @brief Check if the test was run.
     * 
     * @return true test was run.
     * @return false test was not run.
     */
    bool result_ready() const;

    /**
     * @brief Get the result of the test.
     * 
     * @return true the test passed.
     * @return false the test failed.
     */
    bool get_result() const;

    /**
     * @brief Run the test.
     * 
     * This method is called to run the test.
     * It calls the setup() method, the run() method, and the teardown() method in sequence.
     */
    void operator()();
};

Test::STATE operator&(Test::STATE a, Test::STATE b);
Test::STATE operator|(Test::STATE a, Test::STATE b);

}