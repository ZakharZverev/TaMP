#include "bisection_method.h"
#include <iostream>

double BisectionMethod::f(double x) {
    return x * x - 2;
}

double BisectionMethod::findRoot(double lower, double upper, double tolerance) {
    if (f(lower) * f(upper) >= 0) {
        std::cerr << "The function does not have opposite signs at the interval endpoints." << std::endl;
        return -1;
    }

    double mid = lower;
    while ((upper - lower) >= tolerance) {
        mid = (lower + upper) / 2;

        if (f(mid) == 0.0)
            break;
        else if (f(mid) * f(lower) < 0)
            upper = mid;
        else
            lower = mid;
    }

    return mid;
}

