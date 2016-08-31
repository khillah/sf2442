#pragma once

#include "Coordinates.hpp"
#include <cmath>

struct Vector
{
    Vector(double x, double y) :
        x(x),
        y(y)
    {}

    Vector(const Coordinates& begin, const Coordinates& end) :
        x(end.x - begin.x),
        y(end.y - begin.y)
    {}

    Vector& normalize()
    {
        double len = std::sqrt(x * x + y * y);
        x /= len;
        y /= len;
        return *this;
    }

    Vector& addVectorMultipliedByFloat(const Vector& vec, double multiplier)
    {
        x += vec.x * multiplier;
        y += vec.y * multiplier;

        return *this;
    }

    Vector& multiply(double multiplier)
    {
        x *= multiplier;
        y *= multiplier;

        return *this;
    }

    Vector& cut()
    {
        x = std::ceil(x);
        y = std::ceil(y);

        return *this;
    }

    double angleBetweenVectorsNormalized(const Vector& v) const
    {
        double dot = x * v.x + y * v.y;     //dot product
        double det = x * v.y - y * v.x;     // determinant
        return std::fabs(atan2(det, dot));
    }

    Coordinates translatePoint(const Coordinates& point) const
    {
        return
        {
            static_cast<int>(std::round(point.x + x)),
            static_cast<int>(std::round(point.y + y))
        };
    }

    Coordinates translateGivenPointTimes(const Coordinates& point, int times) const
    {
        return
        {
            static_cast<int>(point.x + times * x),
            static_cast<int>(point.y + times * y)
        };
    }

    double x;
    double y;
};
