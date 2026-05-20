//
// Created by Saeid Yazdani on 4/29/2023.
//

#pragma once

#include <string>

namespace embedonix::simplelibs::stringtools::trim {

/**
 * @brief Trim whitespace from the left side of a string.
 * @param s String to modify in place.
 */
void left(std::string& s);

/**
 * @brief Trim whitespace from the right side of a string.
 * @param s String to modify in place.
 */
void right(std::string& s);

/**
 * @brief Trim whitespace from both sides of a string.
 * @param s String to modify in place.
 */
void both_sides(std::string& s);

/**
 * @brief Return a copy with whitespace trimmed from the left side.
 * @param s String to trim.
 * @return Left trimmed copy of `s`.
 */
std::string left_copy(std::string s);

/**
 * @brief Return a copy with whitespace trimmed from the right side.
 * @param s String to trim.
 * @return Right trimmed copy of `s`.
 */
std::string right_copy(std::string s);

/**
 * @brief Return a copy with whitespace trimmed from both sides.
 * @param s String to trim.
 * @return Trimmed copy of `s`.
 */
std::string both_sides_copy(std::string s);

} // End namespace namespace embedonix::simplelibs::stringtools
