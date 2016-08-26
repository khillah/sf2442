#pragma once

#include <cmath>

struct Coordinates
{
    Coordinates()
    {}

    Coordinates(int x, int y) :
        x(x),
        y(y)
    {}

    double distance(const Coordinates& point) const
    {
        return std::sqrt((point.x - x) * (point.x - x) +
                         (point.y - y) * (point.y - y));
    }

    int x;
    int y;
};
