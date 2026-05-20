#include <cctype>
#include <embedonix/simplelibs/stringtools/trim.h>

namespace embedonix::simplelibs::stringtools::trim {

void left(std::string& s) {
  s.erase(s.begin(), std::ranges::find_if(s.begin(), s.end(),
                                  [](unsigned char ch) {
                                    return !std::isspace(ch);
                                  }));
}

void right(std::string& s) {
  // base() converts the reverse iterator to the first trailing whitespace.
  s.erase(std::ranges::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) {
                         return !std::isspace(ch);
                       }).base(), s.end());
}

void both_sides(std::string& s) {
  right(s);
  left(s);
}

std::string left_copy(std::string s) {
  left(s);
  return s;
}

std::string right_copy(std::string s) {
  right(s);
  return s;
}

std::string both_sides_copy(std::string s) {
  both_sides(s);
  return s;
}

} // End namespace namespace embedonix::simplelibs::stringtools
