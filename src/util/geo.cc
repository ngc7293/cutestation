// #include <numbers>
#include <numeric>

#include <cmath>

#include "geo.hh"

namespace util::geo {

namespace {
    constexpr double rad(double deg) { return (deg * M_PI) / 180; }
    constexpr double deg(double rad) { return (rad * 180) / M_PI; }

    constexpr point rad(point p) { return {rad(p.lat), rad(p.lon)}; }
}

double bearing(point from, point to)
{
    from = rad(from);
    to = rad(to);

    double bearing = std::atan2(
        std::cos(to.lat) * std::sin(to.lon - from.lon),
        std::cos(from.lat) * std::sin(to.lat) - std::sin(from.lat) * std::cos(to.lat) * std::cos(to.lon - from.lon)
    );

    return deg(bearing < 0 ? bearing + M_PI * 2 : bearing);
}

double distance(point from, point to)
{
    from = rad(from);
    to = rad(to);

    double a = std::sin((to.lat - from.lat) / 2) * std::sin((to.lat - from.lat) / 2) +
               std::cos(from.lat) * std::cos(to.lat) *
               std::sin((to.lon - from.lon) / 2) * std::sin((to.lon - from.lon) / 2);

    return 2 * atan2(std::sqrt(a), std::sqrt(1-a)) * constants::r_earth;
}

} // namespaces