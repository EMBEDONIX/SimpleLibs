//
// Created by YAZDANI on 21.04.2023.
//

#pragma once

#include <concepts>
#include <type_traits>

namespace embedonix::simplelibs::math::basic_operations {

/**
 * @brief Concept for integral types except bool.
 * @tparam T Type to check.
 *
 * @note `bool` is excluded even though it is an integral type in C++.
 */
template<class T>
concept IntegralNumber = std::is_integral_v<T> and not std::same_as<T, bool>;

/**
 * @brief Check whether an integral value is even.
 * @param num Value to check.
 * @return `true` when `num` is divisible by 2.
 */
constexpr bool is_even(IntegralNumber auto num) {
  return ((num % 2) == 0);
}

/**
 * @brief Check whether an integral value is odd.
 * @param num Value to check.
 * @return `true` when `num` is not divisible by 2.
 */
constexpr bool is_odd(IntegralNumber auto num) {
  return ((num % 2) not_eq 0);
}

} // End Namespace embedonix::simplelibs::math::basic_operations
