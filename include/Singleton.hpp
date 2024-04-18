/**
 * @file Singleton.hpp
 * @author TL044CN
 * @brief 
 * @version 0.2
 * @date 2024-03-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

/**
 * @brief Singleton base class for making other Classes into Singletons
 *
 * @tparam T the Class to make into a Singleton
 */
template<typename T>
class Singleton {
private:
    static bool mInitialized;
public:
    /**
     * @brief Get the Instance of the Singleton Object
     *
     * @return T& reference to the Singleton Object
     */
    static T& getInstance() {
        static T instance;
        return instance;
    }

    /**
     * @brief Destroys a Singleton object
     */
    static void destroy() {
        delete& getInstance();
    }

    /**
     * @brief Resets the Singleton by destroying it and reinitializing it
     *
     */
    static void reset() {
        destroy();
        getInstance();
    }

protected:
    Singleton() {};

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
