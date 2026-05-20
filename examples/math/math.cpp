//
// Created by Saeid Yazdani on 12/9/2023.
//

#include <iostream>
#include <embedonix/simplelibs/stringtools/print.h>
#include <embedonix/simplelibs/math/basic.h>

int main() {

    std::cout << "Welcome to MATH example!" << std::endl;

    std::cout << true << std::endl;


    std::cout << "is 1 even? " << std::boolalpha <<
              embedonix::simplelibs::math::basic_operations::is_even(1)
              << std::endl;
    std::cout << "is 1 odd? " << std::boolalpha <<
              embedonix::simplelibs::math::basic_operations::is_odd(1)
              << std::endl;


    std::cout << "is 2 even? " << std::boolalpha <<
              embedonix::simplelibs::math::basic_operations::is_even(2)
              << std::endl;
    std::cout << "is 2 odd? " << std::boolalpha <<
              embedonix::simplelibs::math::basic_operations::is_odd(2)
              << std::endl;


    return 0;
}
