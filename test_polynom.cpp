#include "test_polynom.h"


int main() {
    Vector<double, 3> v0;
    Vector<double, 3> v1 = {1.25, 3, 2.7};
    Vector<double, 3> v2(v1);
    Vector<double, 3> v4 = {-5, 7, 8};
    std::cout << v1.norm() << std::endl;
    Vector<double, 3> v3 = 2 * v1 / 3 + 7 * v4 - v2;
    std::cout << v3;
    std::cout << (v1 == v2) << " " << (v1 == v3) << std::endl;
    Vector<double, 4> v5 = {1, 2, 3};
    std::cout << v5;

    Vector<double, -1> v0_dynamic;
    Vector<double, -1> v1_dynamic = {1.25, 3, 2.7};
    Vector<double, -1> v2_dynamic(v1_dynamic);
    Vector<double, -1> v4_dynamic = {-5, 7, 8};
    std::cout << v1_dynamic.norm() << std::endl;
    Vector<double, -1> v3_dynamic = 2 * v1_dynamic / 3 + 7 * v4_dynamic - v2_dynamic;
    std::cout << v3_dynamic;
    std::cout << (v1_dynamic == v2_dynamic) << " " << (v1_dynamic == v3_dynamic) << std::endl;

    Polynom<double, 3> p0;
    Polynom<double, 3> p1 = {1.25, 3, 2.7};
    Polynom<double, 3> p2(p1);
    Polynom<double, 3> p4 = {-5, 7, 8};
    Polynom<double, 3> p3 = 2 * p1 / 3 + 7 * p4 - p2;
    std::cout << p3;
    std::cout << (p1 == p2) << " " << (p1 == p3) << std::endl;

    Polynom<double, -1> p0_mod;
    Polynom<double, -1> p1_mod = {{0, 1.25},
                                  {1, 3},
                                  {2, 2.7}};
    Polynom<double, -1> p2_mod(p1_mod);
    Polynom<double, -1> p4_mod = {{0, -5},
                                  {1, 7},
                                  {2, 8}};
    Polynom<double, -1> p3_mod = 2 * p1_mod / 3 + 7 * p4_mod - p2_mod;
    std::cout << p3_mod;
    std::cout << (p1_mod == p2_mod) << " " << (p1_mod == p3_mod) << std::endl;

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