#ifndef UTIL_GEO_HH_
#define UTIL_GEO_HH_

#include <numbers>

#include <cmath>

namespace util::geo {

namespace constants {
    const double r_earth = 6.371e6;
}

struct point {
    double lat;
    double lon;
};

double bearing(point from, point to);
double distance(point from, point to);

} // namespaces

#endif