#ifndef BISECTION_METHOD_H
#define BISECTION_METHOD_H

class BisectionMethod {
public:
    static double f(double x);
    static double findRoot(double lower, double upper, double tolerance = 0.0001);
};

#endif // BISECTION_METHOD_H
