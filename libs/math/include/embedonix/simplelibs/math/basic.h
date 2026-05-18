//
// Created by YAZDANI on 21.04.2023.
//

#pragma once

#include <concepts>
#include <type_traits>

/**
 * @brief Contains basic math operations
 */
namespace embedonix::simplelibs::math::basic_operations {

/**
 * Check if a value type is an integer.
 * @note bool is an integer by design, so I explicitly exlude it.
 * @tparam T Type to check
 */
template<class T>
concept IntegralNumber = std::is_integral_v<T> and not std::same_as<T, bool>;

/**
 * Check if a numeric value is even.
 * @tparam T Type of the parameter
 * @param t value of the parameter
 * @return true if value is even
 */
constexpr bool is_even(IntegralNumber auto num) {
  return ((num % 2) == 0);
}

/**
 * Check if a numeric value is odd.
 * @tparam T Type of the parameter
 * @param t value of the parameter
 * @return true if value is odd
 */
constexpr bool is_odd(IntegralNumber auto num) {
  return ((num % 2) not_eq 0);
}

} // End Namespace embedonix::simplelibs::math::basic_operations
