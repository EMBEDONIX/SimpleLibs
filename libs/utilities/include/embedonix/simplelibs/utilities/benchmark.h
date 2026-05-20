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
     * @brief Measure one function call in microseconds.
     * @tparam F Callable type.
     * @tparam Args Callable argument types.
     * @param func Callable to run.
     * @param args Arguments forwarded to `func`.
     * @return Elapsed time in microseconds.
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
    * @brief Measure average execution time of repeated function calls.
    * @tparam F Callable type.
    * @tparam Args Callable argument types.
    * @param runTimes Number of times to run `func`.
    * @param func Callable to run.
    * @param args Arguments forwarded to `func`.
    * @return Average elapsed time in microseconds.
    * @throws std::invalid_argument If `runTimes` is zero.
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
     * @brief Store the current time in a reusable timer object.
     * @tparam Clock Clock type to use.
     * @param timer Time point updated with `Clock::now()`.
     */
    template<typename Clock = std::chrono::high_resolution_clock>
    inline void start_timer(std::chrono::time_point<Clock>& timer) noexcept {
        timer = Clock::now();
    }

    /**
     * @brief Return elapsed time since a stored timer value.
     * @tparam Clock Clock type used by `timer`.
     * @tparam Duration Duration type to return.
     * @param timer Time point holding the start time.
     * @return Duration from `timer` until now.
     */
    template<typename Clock = std::chrono::high_resolution_clock,
             typename Duration = std::chrono::microseconds>
    inline Duration stop_timer(const std::chrono::time_point<Clock>& timer) noexcept {
        auto end = Clock::now();
        return std::chrono::duration_cast<Duration>(end - timer);
    }

    /**
     * @brief Format a duration with a unit suffix.
     * @tparam Duration Duration type.
     * @param duration Duration value to format.
     * @param space When `true`, insert a space between count and unit.
     * @return Formatted duration string.
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
