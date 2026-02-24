#pragma once   

#include <cmath>

namespace math {
    inline constexpr double PI = 3.14159265358979323846;
    inline constexpr double TAU = 2.0 * PI;
    inline constexpr double E  = 2.71828182845904523536;

    // optional: compute using standard functions
    #undef M_PI
    inline double M_PI = std::acos(-1.0);
}