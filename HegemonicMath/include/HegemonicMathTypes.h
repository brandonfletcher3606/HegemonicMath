#pragma once

namespace Hegemonic
{
    const double pi = 3.14159265358979323846;
    const double pi2 = 2.0 * pi;
    const double halfpi = 0.5 * pi;
    const double quarterpi = 0.25 * pi;
    const double inversepi = 1.0f / pi;
    const double inversepi2 = 1.0f / pi2;
    const double sqrt2 = 1.41421356237309504880;
    const double sqrt3 = 1.73205080756887729352;
    const double sqrtinverse2 = 0.70710678118654752440;
    const double sqrtinverse3 = 0.57735026918962576450;
    const double deg2rad = pi / 180.0;
    const double rad2deg = 180.0f / pi;

    // The multiplier to convert seconds to milliseconds.
    const double ks2ms = 1000.0;

    // The multiplier to convert milliseconds to seconds.
    const double ms2s = 0.001;

    // A huge number that should be larger than any valid number used.
    const double infinity = 1e30;

    // Smallest positive number where 1.0 + FLOAT_EPSILON != 0
    const float floatError = 1.192092896e-07;

    // Smallest positive number where 1.0 + DOUBLE_EPSILON != 0
    const double doubleError = 1.192092896e-14;
}