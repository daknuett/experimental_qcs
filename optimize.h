#ifndef optimize_h_included_
#define optimize_h_included_

#include <math.h>

inline int
isclose(double a, double b, double eps)
{
    return abs(a - b) < eps;
}

inline int
fisclose(float a, float b, float eps)
{
    return fabs(a - b) < eps;
}

#endif
