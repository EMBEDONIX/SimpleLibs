//
// Created by Saeid Yazdani on 5/7/2023.
//

#pragma once

#include <chrono>
#include <cstddef>
#include <format>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace embedonix::simplelibs::utilities::benchmark::measure {
    /**
     * Measure execution time of a function in microseconds
     * @tparam F Function Type
     * @tparam Args Arguments Type
     * @param func Function name
     * @param args Arguments to the function
     * @return
     */
    template<typename F, typename... Args>
    double function_execution_time(F func, Args &&... args) {
        auto startTime =
                std::chrono::high_resolution_clock::now();
        // Execute the function
        func(std::forward<Args>(args)...);
        return std::chrono::duration_cast<std::chrono::microseconds>
                (std::chrono::high_resolution_clock::now() - startTime).count();
    }

    /**
    * Measures average execution time of a function for given number
    * of executions in microseconds
    * @tparam F Function Type
    * @tparam Args Arguments Type
    * @param runTimes Number of times to execute the function
    * @param func Function name
    * @param args Arguments to the function
    * @return Average duration it took to execute @b{func} for
    */
    template<typename F, typename... Args>
    double function_average_execution_time(std::size_t runTimes, F func, Args &&... args) {
        if (runTimes == 0) {
            throw std::invalid_argument("runTimes must be greater than zero");
        }

        auto sum = 0.0;
        for (std::size_t i = 0; i < runTimes; ++i) {
            auto startTime =
                    std::chrono::high_resolution_clock::now();
            // Execute the function
            func(std::forward<Args>(args)...);
            sum += std::chrono::duration_cast<std::chrono::microseconds>
                    (std::chrono::high_resolution_clock::now() - startTime).count();
        }
        return (sum / runTimes);
    }


        /**
         * Starts a timer for a future use
         * @tparam Clock Type of the clock to be used
         * @param timer time_point for the timer
         */
    template<typename Clock = std::chrono::high_resolution_clock>
    inline void start_timer(std::chrono::time_point<Clock>& timer) noexcept {
        timer = Clock::now();
    }

    /**
     * Stops a previously set time_point and returns the duration
     * @tparam Clock Type of the clock to be used
     * @tparam Duration Resolution of the duration to return
     * @param timer The timer object holding the start time
     * @return The duration from the start time until now
     */
    template<typename Clock = std::chrono::high_resolution_clock,
             typename Duration = std::chrono::microseconds>
    inline Duration stop_timer(const std::chrono::time_point<Clock>& timer) noexcept {
        auto end = Clock::now();
        return std::chrono::duration_cast<Duration>(end - timer);
    }

    /**
     * Formats a duration count with unit deduced from Duration type
     * @tparam Duration Duration type
     * @param duration Duration object
     * @param space Adds a space between count and unit
     * @return
     */
    template <typename Duration>
    inline
    std::string format_duration(Duration duration, bool space = false)
    noexcept {
        using namespace std::chrono;

        // Extract count value from the duration
        auto count = duration.count();

        // Format the output based on the duration type
        if constexpr (std::is_same_v<Duration, nanoseconds>) {
            return std::format("{}{}ns", count, space ? " " : "");
        } else if constexpr (std::is_same_v<Duration, milliseconds>) {
            return std::format("{}{}ms", count, space ? " " : "");
        } else if constexpr (std::is_same_v<Duration, microseconds>) {
            return std::format("{}{}us", count, space ? " " : "");
        } else if constexpr (std::is_same_v<Duration, seconds>) {
            return std::format("{}{}s", count, space ? " " : "");
        } else {
            return std::format("{}{}(unknown unit)", count, space ? " " : "");
        }
    }

}
