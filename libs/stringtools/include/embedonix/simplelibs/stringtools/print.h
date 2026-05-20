//
// Created by Saeid Yazdani on 4/30/2023.
//

#pragma once

#include <iostream>
#include <ranges>

namespace embedonix::simplelibs::stringtools::print {

/**
 * @brief Print all elements of a container to a stream.
 * @tparam CONTAINER Container type with `std::begin` and `std::end` support.
 * @tparam DELIMITER Printable delimiter type.
 * @param container Container to print.
 * @param delimiter Value printed between elements.
 * @param addNewLine When `true`, write a newline after the final element.
 * @param os Stream to print into.
 */
template<class CONTAINER, typename DELIMITER = char>
void container(const CONTAINER& container, DELIMITER delimiter = ' ',
                     bool addNewLine = true,
                     std::ostream& os = std::cout) {
  auto it = std::begin(container);
  auto end = std::end(container);

  if (it != end) { // There is at least one element available :)
    os << *it; // Print first element
    for (++it; it != end; ++it) { // Print the rest, if available
      os << delimiter << *it;
    }
    if(addNewLine) {
      os << std::endl;
    }
  }
}

} // End namespace embedonix::simplelibs::stringtools
