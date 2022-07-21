#include "test_polynom.h"


int main() {
    Polynom<double, 6> test_1 = {5, -2, 25, -12, 3, 10};
    Polynom<double, 6> test_2 = {2, -1, 5, 0, 0, 0};
    Polynom<double, 6> remainder;
    Polynom<double, 6> result;

    result = polynomial_long_division(test_1, test_2, remainder);
    std::cout << result;
    std::cout << remainder;


    Polynom<double, -1> map_1 = {{0, 5},
                                 {1, -2},
                                 {2, 25},
                                 {3, -12},
                                 {4, 3},
                                 {5, 10}};
    Polynom<double, -1> map_2 = {{0, 2},
                                 {1, -1},
                                 {2, 5}};
    Polynom<double, -1> map_remainder;
    Polynom<double, -1> map_result;

    map_result = polynomial_long_division(map_1, map_2, map_remainder);
    std::cout << map_result;
    std::cout << map_remainder;


}